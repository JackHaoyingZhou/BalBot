/**
 * @file HBridge.h
 * @brief Class for H-bridge control for Arduino and Mbed
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <DigitalOut.h>
#include <PwmOut.h>

/**
 * Class Declaration
 */
class HBridge
{
public:
	HBridge(
		Platform::pin_t pin_pwm,
		Platform::pin_t pin_fwd,
		Platform::pin_t pin_rev,
		float vcc);
	void set_voltage(float v_cmd);
protected:
	PwmOut pwm_out;
	DigitalOut fwd_out;
	DigitalOut rev_out;
	float vcc, vcc_inv;
};
