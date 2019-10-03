/**
 * @file MotorL.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "MotorL.h"
#include <MotorConfig.h>
#include <BalBot.h>
#include <PinDefs.h>
#include <Imu.h>
#include <HBridgeMotor.h>
#include <QuadEncoder.h>
#include <DiscreteFilter.h>

namespace MotorL
{
	// Hardware Interfaces
	HBridgeMotor motor(pin_lm_pwm, pin_lm_fwd, pin_lm_rev, Vb);
	QuadEncoder encoder(pin_lenc_a, pin_lenc_b, MotorConfig::cnt_per_rev);

	// Digital Filters
	DiscreteFilter angle_diff = DiscreteFilter::make_dif(f_ctrl);

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
void MotorL::init()
{
	motor.init();
	motor.enable();
	encoder.init();
	attachInterrupt(digitalPinToInterrupt(pin_lenc_a), isr_A, CHANGE);
	attachInterrupt(digitalPinToInterrupt(pin_lenc_b), isr_B, CHANGE);
}

/**
 * @brief Updates motor state estimates.
 */
void MotorL::update()
{
	angle = MotorConfig::direction * encoder.read() - Imu::get_pitch();
	velocity = angle_diff.update(angle);
}

/**
 * @brief Sends given voltage command to motor.
 */
void MotorL::set_voltage(float v_cmd)
{
	motor.set_voltage(MotorConfig::direction * v_cmd);
}

/**
 * @brief Returns encoder angle estimate.
 */
float MotorL::get_angle()
{
	return angle;
}

/**
 * @brief Returns encoder velocity estimate.
 */
float MotorL::get_velocity()
{
	return velocity;
}

/**
 * @brief Motor encoder A ISR.
 */
void MotorL::isr_A()
{
	encoder.interrupt_A();
}

/**
 * @brief Motor encoder B ISR.
 */
void MotorL::isr_B()
{
	encoder.interrupt_B();
}