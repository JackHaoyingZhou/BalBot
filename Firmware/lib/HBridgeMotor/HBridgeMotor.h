/**
 * @file HBridgeMotor.h
 * @brief Class for H-bridge motor control.
 * @author Dan Oates (WPI Class of 2020)
 * 
 * An H-bridge motor interface has 3 pins:
 * - pin_pwm: PWM input (speed control)
 * - pin_fwd: Forward enable pin
 * - pin_rev: Reverse enable pin
 * 
 * This class automatically handles pin assignments
 * with a voltage command abstraction layer.
 */
#pragma once
#include <Arduino.h>

class HBridgeMotor
{
public:
	HBridgeMotor(uint8_t pin_pwm, uint8_t pin_fwd, uint8_t pin_rev, float v_supply);
	void init();
	void enable();
	void disable();
	void brake();
	void set_voltage(float voltage);
private:
	uint8_t pin_pwm, pin_fwd, pin_rev;
	float v_supply, dac_per_volt;
	bool enabled;
};