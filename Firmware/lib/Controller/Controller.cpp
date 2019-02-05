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
	// Pitch PID Controller
	Pid pid_pitch(
		pid_pitch_kp,
		pid_pitch_ki,
		pid_pitch_kd,
		-v_bat, v_bat, f_ctrl);

	// State Variables
	float lin_vel = 0.0f;	// Linear velocity [m/s]
	float yaw_vel = 0.0f;	// Yaw velocity [rad/s]
	float v_cmd_L = 0.0f;	// Left motor voltage cmd [V]
	float v_cmd_R = 0.0f;	// Right motor voltage cmd [V]
}

/**
 * @brief Runs one control loop.
 */
void Controller::update()
{
	// Estimate velocities from encoders
	const float lin_vel_L = wheel_radius * MotorL::get_velocity();
	const float lin_vel_R = wheel_radius * MotorR::get_velocity();
	lin_vel = 0.5 * (lin_vel_L + lin_vel_R);
	yaw_vel = (lin_vel_R - lin_vel_L) * wheel_base_inv;

	// Open-loop velocity control
	const float v_vel = open_loop_vel_gain * Bluetooth::get_vel_cmd();
	const float v_yaw = open_loop_yaw_gain * Bluetooth::get_yaw_cmd();

	// Closed-loop pitch control
	const float pitch_setpt = 0.0f;
	const float pitch_error = pitch_setpt - Imu::get_pitch();
	const float v_pitch = -pid_pitch.update(pitch_error);
	const float v_ff_L = motor_kv * MotorL::get_velocity();
	const float v_ff_R = motor_kv * MotorR::get_velocity();

	// Fused voltage commands
	v_cmd_L = v_pitch + v_vel - v_yaw + v_ff_L;
	v_cmd_R = v_pitch + v_vel + v_yaw + v_ff_R;
	v_cmd_L = clamp_limit(v_cmd_L, -v_bat, v_bat);
	v_cmd_R = clamp_limit(v_cmd_R, -v_bat, v_bat);
}

/**
 * @brief Returns linear velocity estimate [m/s].
 */
float Controller::get_lin_vel()
{
	return lin_vel;
}

/**
 * @brief Returns yaw velocity estimate [rad/s].
 */
float Controller::get_yaw_vel()
{
	return yaw_vel;
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