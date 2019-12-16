/**
 * @file Controller.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include <Controller.h>
#include <MotorConfig.h>
#include <Bluetooth.h>
#include <Imu.h>
#include <MotorL.h>
#include <MotorR.h>
#include <CppUtil.h>
#include <SlewLimiter.h>
#include <PID.h>
using MotorConfig::Vb;
using MotorConfig::Kv;
using MotorConfig::Kt;
using MotorConfig::R;
using CppUtil::clamp;

/**
 * Namespace Definitions
 */
namespace Controller
{
	// External Constants
	const float f_ctrl = 100.0f;
	const float t_ctrl = 1.0f / f_ctrl;

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
	const float pitch_max = 0.8f;	// Max pitch angle [rad]
	const float lin_vel_max = 0.4f;	// Default max linear velocity [rad/s]
	const float lin_acc_max = 0.2f;	// Default max linear acceleratino [rad/s]
	const float yaw_vel_max = 0.8f;	// Default max yaw velocity [rad/s]
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

	// State Variables
	float lin_vel = 0.0f;		// Linear velocity [m/s]
	float lin_vel_cmd = 0.0f;	// Linear velocity command [m/s]
	float yaw_vel = 0.0f;		// Yaw velocity [rad/s]
	float yaw_vel_cmd = 0.0f;	// Yaw velocity command [rad/s]
	float v_cmd_L = 0.0f;		// L motor voltage cmd [V]
	float v_cmd_R = 0.0f;		// R motor voltage cmd [V]

	// Controllers
	PID yaw_pid(yaw_Kp, yaw_Ki, yaw_Kd, -Vb, Vb, f_ctrl);
	ClampLimiter lin_vel_limiter(lin_vel_max);
	SlewLimiter lin_acc_limiter(lin_acc_max, f_ctrl);
	ClampLimiter yaw_vel_limiter(yaw_vel_max);
	ClampLimiter volt_limiter(Vb);

	// Init Flag
	bool init_complete = false;
}

/**
 * @brief Initializes controller subsystems
 */
void Controller::init()
{
	if (!init_complete)
	{
		// Init dependent subsystems
		Bluetooth::init();
		Imu::init();
		MotorL::init();
		MotorR::init();

		// Set init flag
		init_complete = true;
	}
}

/**
 * @brief Runs one control loop iteration
 */
void Controller::update()
{
	// Process teleop commands
	lin_vel_cmd = Bluetooth::get_lin_vel_cmd();
	lin_vel_cmd = lin_acc_limiter.update(lin_vel_cmd);
	lin_vel_cmd = lin_vel_limiter.update(lin_vel_cmd);
	yaw_vel_cmd = yaw_vel_limiter.update(Bluetooth::get_yaw_vel_cmd());

	// Estimate state variables
	lin_vel = dr_div_2 * (MotorL::get_velocity() + MotorR::get_velocity());
	
	// Pitch-Velocity State-Space Control
	const float v_avg_ref = Gv * lin_vel_cmd;
	float v_avg = v_avg_ref
		+ ss_K1 * (0.0f - Imu::get_pitch_vel())
		+ ss_K2 * (0.0f - Imu::get_pitch())
		+ ss_K3 * (lin_vel_cmd - lin_vel);
	v_avg = clamp(v_avg, -Vb, Vb);

	// Yaw velocity control
	const float yaw_ff = Gw * yaw_vel_cmd;
	const float yaw_error = yaw_vel_cmd - Imu::get_yaw_vel();
	const float v_diff = yaw_pid.update(yaw_error, yaw_ff);

	// Motor voltage commands
	v_cmd_L = volt_limiter.update(v_avg - v_diff);
	v_cmd_R = volt_limiter.update(v_avg + v_diff);

	// Disable motors if tipped over
	if(fabsf(Imu::get_pitch()) > pitch_max)
	{
		yaw_pid.reset();
		v_cmd_L = 0.0f;
		v_cmd_R = 0.0f;
	}
}

/**
 * @brief Sets max linear velocity command [rad/s]
 */
void Controller::set_lin_vel_max(float lin_vel_max)
{
	lin_vel_limiter.set_min(-lin_vel_max);
	lin_vel_limiter.set_max(+lin_vel_max);
}

/**
 * @brief Sets max linear acceleration command [rad/s]
 */
void Controller::set_lin_acc_max(float lin_acc_max)
{
	lin_acc_limiter.set_min(-lin_acc_max);
	lin_acc_limiter.set_max(+lin_acc_max);
}

/**
 * @brief Sets max yaw velocity command [rad/s]
 */
void Controller::set_yaw_vel_max(float yaw_vel_max)
{
	yaw_vel_limiter.set_min(-yaw_vel_max);
	yaw_vel_limiter.set_max(+yaw_vel_max);
}

/**
 * @brief Returns linear velocity estimate [m/s]
 */
float Controller::get_lin_vel()
{
	return lin_vel;
}

/**
 * @brief Returns left motor voltage command [V]
 */
float Controller::get_motor_L_cmd()
{
	return v_cmd_L;
}

/**
 * @brief Returns right motor voltage command [V]
 */
float Controller::get_motor_R_cmd()
{
	return v_cmd_R;
}