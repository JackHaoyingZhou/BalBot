/**
 * @file HBridge.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "HBridge.h"
#include <CppUtil.h>
using Platform::pin_t;

/**
 * @brief Constructs H-bridge interface
 * @param pin_pwm ID of pwm output pin
 * @param pin_fwd ID of forward enable output
 * @param pin_rev ID of reverse enable output
 * @param vcc Supply voltage [V]
 */
HBridge::HBridge(pin_t pin_pwm, pin_t pin_fwd, pin_t pin_rev, float vcc) :
	pwm_out(pin_pwm),
	fwd_out(pin_fwd),
	rev_out(pin_rev)
{
	this->vcc = vcc;
	this->vcc_inv = 1.0f / vcc;
}

/**
 * @brief Sets H-bridge output voltage via PWM
 * @param v_cmd Voltage command in range [-vcc, +vcc]
 * 
 * Note: Commands out of range are automatically saturated.
 */
void HBridge::set_voltage(float v_cmd)
{
	v_cmd = CppUtil::clamp(v_cmd, -vcc, +vcc);
	pwm_out.write(fabsf(v_cmd) * vcc_inv);
	fwd_out.write(v_cmd > 0.0f);
	rev_out.write(v_cmd < 0.0f);
}
