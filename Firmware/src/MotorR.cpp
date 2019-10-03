/**
 * @file MotorR.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "MotorR.h"
#include <MotorConfig.h>
#include <BalBot.h>
#include <Imu.h>
#include <HBridgeMotor.h>
#include <QuadEncoder.h>
#include <DiscreteFilter.h>
#include <PinChangeInt.h>

namespace MotorR
{
	// Pin Definitions
	const uint8_t pin_enable = 8;	// H-bridge enable
	const uint8_t pin_pwm = 10;		// H-bridge PWM
	const uint8_t pin_fwd = 12;		// H-bridge forward enable
	const uint8_t pin_rev = 13;		// H-bridge reverse enable
	const uint8_t pin_enc_a = 5;	// Encoder channel A
	const uint8_t pin_enc_b = 4;	// Encoder channel B

	// Hardware Interfaces
	HBridgeMotor motor(pin_pwm, pin_fwd, pin_rev, BalBot::v_bus);
	QuadEncoder encoder(pin_enc_a, pin_enc_b, MotorConfig::cnt_per_rev);

	// Digital Filters
	DiscreteFilter angle_diff = DiscreteFilter::make_dif(BalBot::f_ctrl);

	// State Variables
	float angle;		// Encoder angle [rad]
	float velocity;		// Angular velocity [rad/s]

	// Private functions
	void isr_A();
	void isr_B();
}

/**
 * @brief Initializes drive motor.
 * Enables motor and encoder, and sets up encoder ISRs.
 */
void MotorR::init()
{
	pinMode(pin_enable, OUTPUT);
	digitalWrite(pin_enable, HIGH);
	motor.init();
	motor.enable();
	encoder.init();
	attachPinChangeInterrupt(pin_enc_a, isr_A, CHANGE);
	attachPinChangeInterrupt(pin_enc_b, isr_B, CHANGE);
}

/**
 * @brief Updates motor state estimates.
 */
void MotorR::update()
{
	angle = MotorConfig::direction * encoder.read() - Imu::get_pitch();
	velocity = angle_diff.update(angle);
}

/**
 * @brief Sends given voltage command to motor.
 */
void MotorR::set_voltage(float v_cmd)
{
	motor.set_voltage(MotorConfig::direction * v_cmd);
}

/**
 * @brief Returns encoder angle estimate.
 */
float MotorR::get_angle()
{
	return angle;
}

/**
 * @brief Returns encoder velocity estimate.
 */
float MotorR::get_velocity()
{
	return velocity;
}

/**
 * @brief Motor encoder A ISR.
 */
void MotorR::isr_A()
{
	encoder.interrupt_A();
}

/**
 * @brief Motor encoder B ISR.
 */
void MotorR::isr_B()
{
	encoder.interrupt_B();
}