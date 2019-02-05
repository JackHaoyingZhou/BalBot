/**
 * @file main.cpp
 * @brief Main control code for BalBot.
 * @author Dan Oates (WPI Class of 2020)
 */

// External Libraries
#include <Arduino.h>
#include <CppUtil.h>
#include <Timer.h>
#include <Pid.h>

// Project Libraries
#include <BalBot.h>
#include <PinDefs.h>
#include <Imu.h>
#include <MotorL.h>
#include <MotorR.h>
#include <Bluetooth.h>

/**
 * Macros
 */

// Program estimates max control frequency.
// #define GET_MAX_CTRL_FREQ

// Disables motor control.
// #define DISABLE_MOTORS

/**
 * Controller Interfaces
 */
Pid pid_pitch(
	pid_pitch_kp,
	pid_pitch_ki,
	pid_pitch_kd,
	-v_bat, v_bat, f_ctrl);
Timer timer;

/**
 * State Variables
 */
float pos_cmd = 0.0f;

/**
 * @brief Initializes Balbot.
 */
void setup()
{
	// Initialize Peripherals
	Bluetooth::init();
	Imu::init();

	// Initialize Motors
	pinMode(pin_motor_en, OUTPUT);
	digitalWrite(pin_motor_en, HIGH);
	MotorL::init();
	MotorR::init();
}

/**
 * Balbot Control Loop.
 */
void loop()
{
	// Start timing
	timer.tic();

	// Update namespaces
	Imu::update();
	MotorL::update();
	MotorR::update();
	Bluetooth::update();

	// Estimate velocities from encoders
	/*
	const float lin_vel_L = wheel_radius * MotorL::get_velocity();
	const float lin_vel_R = wheel_radius * MotorR::get_velocity();
	const float lin_vel = 0.5 * (lin_vel_L + lin_vel_R);
	const float yaw_vel = (lin_vel_R - lin_vel_L) * wheel_base_inv;
	*/

	// Open-loop velocity control
	const float v_vel = open_loop_vel_gain * Bluetooth::get_vel_cmd();
	const float v_yaw = open_loop_yaw_gain * Bluetooth::get_yaw_cmd();

	// Control pitch with voltage
	const float pitch_setpt = 0.0f;
	const float pitch_error = pitch_setpt - Imu::get_pitch();
	const float v_pitch = -pid_pitch.update(pitch_error);
	const float v_ff_L = motor_kv * MotorL::get_velocity();
	const float v_ff_R = motor_kv * MotorR::get_velocity();
	float v_cmd_L = v_pitch + v_ff_L + v_vel - v_yaw;
	float v_cmd_R = v_pitch - v_ff_R + v_vel + v_yaw;
	v_cmd_L = clamp_limit(v_cmd_L, -v_bat, v_bat);
	v_cmd_R = clamp_limit(v_cmd_R, -v_bat, v_bat);

	// Send voltage commands to motors
#ifndef DISABLE_MOTORS
	MotorL::set_voltage(v_cmd_L);
	MotorR::set_voltage(v_cmd_R);
#endif

#ifdef GET_MAX_CTRL_FREQ
	// Estimate maximum possible control frequency
	const float f_ctrl_max = 1.0f / timer.toc();
	MotorL::set_voltage(0.0f);
	MotorR::set_voltage(0.0f);
	Serial.println("GET_MAX_CTRL_FREQ");
	Serial.println("Max ctrl freq: " + String(f_ctrl_max));
	while(1);
#endif

	// Maintain timing
	timer.wait_until(t_ctrl);
}