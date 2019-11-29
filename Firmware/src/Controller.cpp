/**
 * @file Controller.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include <Controller.h>
#include <BalBot.h>
#include <MotorConfig.h>
#include <Bluetooth.h>
#include <MotorL.h>
#include <MotorR.h>
#include <Imu.h>
#include <CppUtil.h>
#include <Pid.h>
#include <SlewLimiter.h>
#include <Arduino.h>
using MotorConfig::Vb;
using MotorConfig::Kv;
using MotorConfig::Kt;
using MotorConfig::R;

namespace Controller
{
	// Robot Physical Constants
	const float Ix = 0.00215f;	// Pitch inertia [kg*m^2]
	const float Iz = 0.00110f;	// Yaw inertia [kg*m^2]
	const float m = 0.955f;		// Robot mass [kg]
	const float g = 9.81f;		// Gravity [m/s^2]
	const float dg = 0.062f;	// CG height [m]
	const float dw = 0.085f;	// Wheel to CG Z-axis [m]
	const float dr = 0.034;		// Wheel radius [m]

	// Derived Physical Constants
	const float Mx = Ix*dr/dg;	// Generalized X-mass [kg*m^2]
	const float My = m*dr;		// Generalized Y-mass [kg*m]
	const float Mz = Iz*dr/dw;	// Generalized Z-mass [kg*m^2]
	const float Tg = m*g*dr;	// Gravitational torque [N*m]
	const float Gt = 2.0f*Kt/R;	// Torque-voltage gain [N*m/V]
	const float Gv = Kv/dr;		// Linear back-EMF [V/(m/s)]
	const float Gw = Kv*dw/dr;	// Yaw back-EMF [V/(rad/s)]

	// Controller Constants
	const float pitch_max = 0.5f;	// Max pitch angle [rad]
	const float yaw_max = 1.6f;		// Yaw velocity limit [rad/s]
	const float vel_max = 0.8f;		// Velocity limit [m/s]
	const float acc_max = 0.8f;		// Acceleration limit [m/s^2]
	const float px = 20.0f;			// Pitch-velocity pole [1/s]
	const float pz = 80.0f;			// Yaw velocity pole [1/s]
	const float dr_div_2 = dr/2.0f;	// Half wheel radius [m]

	// Pitch-Velocity State-Space Gains
	const float ss_K1 = Mx*Mx/(Gt*Tg)*px*px*px + 3.0f*Mx/Gt*px;
	const float ss_K2 = 3.0f*Mx/Gt*px*px + Tg/Gt;
	const float ss_K3 = -Mx*My/(Gt*Tg)*px*px*px - Gv;

	// Yaw Velocity PI-Controller Gains
	const float yaw_Kp = 0.0f;
	const float yaw_Ki = 5.0f;
	const float yaw_Kd = 0.0f;

	// Controllers
	Pid yaw_pid(yaw_Kp, yaw_Ki, yaw_Kd, -Vb, Vb, BalBot::f_ctrl);
	SlewLimiter vel_slew(acc_max, BalBot::f_ctrl);

	// State Variables
	float lin_vel = 0.0f;	// Linear velocity [m/s]
	float vel_cmd = 0.0f;	// Linear velocity cmd [m/s]
	float yaw_cmd = 0.0f;	// Yaw velocity cmd [rad/s]
	float v_cmd_L = 0.0f;	// Left motor voltage cmd [V]
	float v_cmd_R = 0.0f;	// Right motor voltage cmd [V]
}

/**
 * @brief Runs one control loop.
 */
void Controller::update()
{
	// Process teleop commands
	vel_cmd = vel_slew.update(Bluetooth::get_vel_cmd());
	vel_cmd = clamp_limit(vel_cmd, -vel_max, vel_max);
	yaw_cmd = clamp_limit(Bluetooth::get_yaw_cmd(), -yaw_max, yaw_max);

	// Estimate state variables
	lin_vel = dr_div_2 * (MotorL::get_velocity() + MotorR::get_velocity());
	
	// Pitch-Velocity State-Space Control
	const float v_avg_ref = Gv * vel_cmd;
	float v_avg = v_avg_ref
		+ ss_K1 * (0.0f - Imu::get_pitch_vel())
		+ ss_K2 * (0.0f - Imu::get_pitch())
		+ ss_K3 * (vel_cmd - lin_vel);
	v_avg = clamp_limit(v_avg, -Vb, Vb);

	// Yaw velocity control
	const float yaw_ff = Gw * yaw_cmd;
	const float yaw_error = yaw_cmd - Imu::get_yaw_vel();
	const float v_diff = yaw_pid.update(yaw_error, yaw_ff);

	// Motor voltage commands
	v_cmd_L = clamp_limit(v_avg - v_diff, -Vb, Vb);
	v_cmd_R = clamp_limit(v_avg + v_diff, -Vb, Vb);

	// Disable motors if tipped over
	if(fabsf(Imu::get_pitch()) > pitch_max)
	{
		yaw_pid.reset();
		v_cmd_L = 0.0f;
		v_cmd_R = 0.0f;
	}
}

/**
 * @brief Returns linear velocity estimate [m/s].
 */
float Controller::get_lin_vel()
{
	return lin_vel;
}

/**
 * @brief Returns left motor voltage command [V].
 */
float Controller::get_motor_L_cmd()
{
	return v_cmd_L;
}

/**
 * @brief Returns right motor voltage command [V].
 */
float Controller::get_motor_R_cmd()
{
	return v_cmd_R;
}