/**
 * @file main.cpp
 * @brief Main control code for BalBot.
 * @author Dan Oates (WPI Class of 2020)
 */

// External Libraries
#include <Arduino.h>
#include <Timer.h>
#include <Pid.h>

// Project Libraries
#include <BalBot.h>
#include <PinDefs.h>
#include <Imu.h>
#include <MotorL.h>
#include <MotorR.h>

/**
 * Macros
 */

// Program prints debug to USB serial at 115200 baud.
// #define SERIAL_DEBUG

// Program estimates max control frequency.
// #define GET_MAX_CTRL_FREQ

/**
 * Controller Interfaces
 */
Pid pid_pitch(
	pid_pitch_kp,
	pid_pitch_ki,
	pid_pitch_kd,
	-v_bat, v_bat, f_ctrl);
Pid pid_pos(
	pid_pos_kp,
	pid_pos_ki,
	pid_pos_kd,
	-pitch_max, pitch_max, f_ctrl);
Timer timer;

/**
 * @brief Initializes Balbot.
 */
void setup()
{
	// Initialize IMU
	Imu::init();

	// Initialize Motors
	pinMode(pin_motor_en, OUTPUT);
	digitalWrite(pin_motor_en, HIGH);
	MotorL::init();
	MotorR::init();

#ifdef SERIAL_DEBUG
	// Initialize Serial Debug
	Serial.begin(115200);
	Serial.println("SERIAL_DEBUG");
#endif
}

/**
 * Balbot Control Loop.
 */
void loop()
{
	// Start timing
	timer.tic();

	// Update state estimators
	Imu::update();
	MotorL::update();
	MotorR::update();

	// Estimate position from encoders
	const float angle_L = MotorL::get_angle();
	const float angle_R = MotorR::get_angle();
	const float robot_pos = r_wheel * 0.5 * (angle_L + angle_R);

	// Control position with pitch
	const float pitch_cmd = pid_pos.update(0.0f - robot_pos);
	
	// Control pitch with voltage
	const float pitch_error = pitch_cmd - Imu::get_pitch();
	const float v_pid = -pid_pitch.update(pitch_error);
	const float v_cmd_L = v_pid + motor_kv * MotorL::get_velocity();
	const float v_cmd_R = v_pid + motor_kv * MotorR::get_velocity();

	// Send voltage commands to motors
	MotorL::set_voltage(v_cmd_L);
	MotorR::set_voltage(v_cmd_R);

#ifdef GET_MAX_CTRL_FREQ
	// Estimate maximum possible control frequency
	const float f_ctrl_max = 1.0f / timer.toc();
	MotorL::set_voltage(0.0f);
	MotorR::set_voltage(0.0f);
	Serial.begin(115200);
	Serial.println("GET_MAX_CTRL_FREQ");
	Serial.println("Max ctrl freq: " + String(f_ctrl_max));
	while(1);
#endif

	// Maintain timing
	timer.wait_until(t_ctrl);
}