/**
 * @file MotorR.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "MotorR.h"
#include <BalBot.h>
#include <PinDefs.h>
#include <Imu.h>
#include <HBridgeMotor.h>
#include <QuadEncoder.h>
#include <Differentiator.h>
#include <PinChangeInt.h>

namespace MotorR
{
	// Hardware Interfaces
	HBridgeMotor motor(pin_rm_pwm, pin_rm_fwd, pin_rm_rev, Vb);
	QuadEncoder encoder(pin_renc_a, pin_renc_b, encoder_cpr);

	// Digital Filters
	Differentiator angle_diff(f_ctrl);

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
	motor.init();
	motor.enable();
	encoder.init();
	attachPinChangeInterrupt(pin_renc_a, isr_A, CHANGE);
	attachPinChangeInterrupt(pin_renc_b, isr_B, CHANGE);
	angle_diff.init();
}

/**
 * @brief Updates motor state estimates.
 */
void MotorR::update()
{
	angle = encoder.read() + Imu::get_pitch();
	velocity = angle_diff.update(angle);
}

/**
 * @brief Sends given voltage command to motor.
 */
void MotorR::set_voltage(float v_cmd)
{
	motor.set_voltage(v_cmd);
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