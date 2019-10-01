/**
 * @file HBridgeMotor.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "HBridgeMotor.h"
#include <CppUtil.h>

/**
 * @brief Constructor for H-bridge motor interface.
 * @param pin_pwm PWM pin (speed control)
 * @param pin_fwd Forward enable pin
 * @param pin_rev Reverse enable pin
 * @param v_supply Supply voltage [V]
 */
HBridgeMotor::HBridgeMotor(uint8_t pin_pwm, uint8_t pin_fwd, uint8_t pin_rev, float v_supply)
{
	this->pin_pwm = pin_pwm;
	this->pin_fwd = pin_fwd;
	this->pin_rev = pin_rev;
	this->v_supply = v_supply;
	this->dac_per_volt = 255.0f / v_supply;
	this->enabled = false;
}

/**
 * @brief Initializes and disables motor.
 */
void HBridgeMotor::init()
{
	pinMode(pin_pwm, OUTPUT);
	pinMode(pin_fwd, OUTPUT);
	pinMode(pin_rev, OUTPUT);
	disable();
}

/**
 * @brief Enables and brakes motor.
 */
void HBridgeMotor::enable()
{
	enabled = true;
	brake();
}

/**
 * @brief Disables and coasts motor.
 */
void HBridgeMotor::disable()
{
	digitalWrite(pin_pwm, 0);
	digitalWrite(pin_fwd, 0);
	digitalWrite(pin_rev, 0);
	enabled = false;
}

/**
 * @brief Brakes motor (if enabled).
 */
void HBridgeMotor::brake()
{
	if(enabled)
	{
		digitalWrite(pin_pwm, 0);
		digitalWrite(pin_fwd, 1);
		digitalWrite(pin_rev, 1);
	}
}

/**
 * @brief Sets motor RMS voltage through PWM (if enabled).
 * @param v_cmd Voltage command [V] (limited to [-v_supply, v_supply])
 */
void HBridgeMotor::set_voltage(float v_cmd)
{
	if(enabled)
	{	
		if(v_cmd == 0.0f)
		{
			brake();
		}
		else
		{
			v_cmd = clamp_limit(v_cmd, -v_supply, v_supply);
			analogWrite(pin_pwm, fabsf(v_cmd) * dac_per_volt);
			if(v_cmd > 0.0f)
			{
				digitalWrite(pin_fwd, 1);
				digitalWrite(pin_rev, 0);
			} 
			else
			{
				digitalWrite(pin_fwd, 0);
				digitalWrite(pin_rev, 1);
			}
		}
	}
}