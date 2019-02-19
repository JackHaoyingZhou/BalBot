/**
 * @file Controller.cpp
 * @author Dan Oates (WPI Class of 2020).
 */
#include "Controller.h"
#include <BalBot.h>
#include <Bluetooth.h>
#include <MotorL.h>
#include <MotorR.h>
#include <Imu.h>
#include <CppUtil.h>
#include <Pid.h>
#include <SlewLimiter.h>

namespace Controller
{
	// Controllers
	Pid yaw_pid(yaw_Kp, yaw_Ki, yaw_Kd, -Vb, Vb, f_ctrl);
	SlewLimiter vel_slew(acc_max, f_ctrl);

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