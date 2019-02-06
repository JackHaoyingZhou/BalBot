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

namespace Controller
{
	// PID Controllers
	Pid pitch_pid(pitch_kp, pitch_ki, pitch_kd, -Vb, Vb, f_ctrl);
	Pid yaw_pid(yaw_kp, yaw_ki, yaw_kd, -Vb, Vb, f_ctrl);
	Pid vel_pid(vel_kp, vel_ki, vel_kd, -pitch_max, pitch_max, f_ctrl);

	// State Variables
	float lin_vel = 0.0f;	// Linear velocity [m/s]
	float v_cmd_L = 0.0f;	// Left motor voltage cmd [V]
	float v_cmd_R = 0.0f;	// Right motor voltage cmd [V]
}

/**
 * @brief Runs one control loop.
 */
void Controller::update()
{
	// Estimate state variables
	lin_vel = Rw_div_2 * (MotorL::get_velocity() + MotorR::get_velocity());

	// Update controllers
	const float vel_error  = Bluetooth::get_vel_cmd() - lin_vel;
	const float pitch_setpt = vel_pid.update(vel_error);
	const float pitch_error = Imu::get_pitch() - pitch_setpt;
	const float v_avg_ff = Kv_div_Rw * lin_vel;
	const float v_avg = pitch_pid.update(pitch_error, v_avg_ff);
	const float yaw_error = Bluetooth::get_yaw_cmd() - Imu::get_yaw_vel();
	const float v_diff = yaw_pid.update(yaw_error);

	// Motor voltage commands
	v_cmd_L = clamp_limit(v_avg - v_diff, -Vb, Vb);
	v_cmd_R = clamp_limit(v_avg + v_diff, -Vb, Vb);
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