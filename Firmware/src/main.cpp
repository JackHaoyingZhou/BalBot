/**
 * @file main.cpp
 * @brief Main control code for BalBot.
 * @author Dan Oates (WPI Class of 2020)
 */

// External Libraries
#include <Arduino.h>
#include <Timer.h>

// Project Libraries
#include <BalBot.h>
#include <Imu.h>
#include <MotorL.h>
#include <MotorR.h>
#include <Bluetooth.h>
#include <Controller.h>

// Global Variables
uint32_t loop_count = 0;		// Control loop counter
Timer timer;					// Controller timer

/**
 * @brief Initializes Balbot.
 */
void setup()
{
	// Initialize Peripherals
	Bluetooth::init();
	Imu::init();

	// Initialize Motors
	MotorL::init();
	MotorR::init();

#if defined(CALIBRATE_IMU)

	// Print IMU calibration values
	Imu::calibrate();
	while(1);

#endif
}

/**
 * Balbot Control Loop.
 */
void loop()
{
	// Start timing
	timer.tic();

	// Update subsystems
	Bluetooth::update();
	Imu::update();
	MotorL::update();
	MotorR::update();
	Controller::update();

#if defined(SERIAL_DEBUG)

	// Print debug info to serial
	MotorL::set_voltage(0.0f);
	MotorR::set_voltage(0.0f);
	if (loop_count % 25 == 0)
	{
		Serial.println("Motor L Angle [rad]: " + String(MotorL::get_angle(), 2));
		Serial.println("Motor R Angle [rad]: " + String(MotorR::get_angle(), 2));
		Serial.println("Pitch Angle [rad]: " + String(Imu::get_pitch(), 2));
		Serial.println();
	}

#elif defined(GET_MAX_CTRL_FREQ)

	// Estimate maximum possible control frequency
	const float f_ctrl_max = 1.0f / timer.toc();
	MotorL::set_voltage(0.0f);
	MotorR::set_voltage(0.0f);
	Serial.println("GET_MAX_CTRL_FREQ");
	Serial.println("Max ctrl freq: " + String(f_ctrl_max));
	while(1);

#else

	// Send voltage commands to motors
	MotorL::set_voltage(Controller::get_motor_L_cmd());
	MotorR::set_voltage(Controller::get_motor_R_cmd());

#endif

	// Maintain loop timing
	loop_count++;
	timer.wait_until(t_ctrl);
}