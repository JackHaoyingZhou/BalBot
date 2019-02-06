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
#include <PinDefs.h>
#include <Imu.h>
#include <MotorL.h>
#include <MotorR.h>
#include <Bluetooth.h>
#include <Controller.h>

/**
 * Macros
 */

// Program estimates max control frequency.
// #define GET_MAX_CTRL_FREQ

// Disables motor control.
// #define DISABLE_MOTORS

// Control loop timer
Timer timer;

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
	Bluetooth::update();
	Imu::update();
	MotorL::update();
	MotorR::update();
	Controller::update();

	// Send voltage commands to motors
#ifndef DISABLE_MOTORS
	MotorL::set_voltage(Controller::get_motor_L_cmd());
	MotorR::set_voltage(Controller::get_motor_R_cmd());
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