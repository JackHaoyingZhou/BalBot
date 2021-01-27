/**
 * @file PwmOut.h
 * @author Dan Oates (WPI Class of 2020)
 */
#include "PwmOut.h"
#include <CppUtil.h>

#if defined(PLATFORM_ARDUINO)

/**
 * @brief Constructs PWM output and writes 0% duty cycle
 * @param pin Platform-specific pin ID
 */
PwmOut::PwmOut(Platform::pin_t pin)
{
	this->pin = pin;
	write(0.0f);
}

/**
 * @brief Sets PWM to given duty cycle
 * @param duty_cycle Duty cycle in range [0,1]
 * 
 * An input of 0 corresponds to 0% and 1 to 100%. Inputs outside of this range
 * are automatically clamp limited.
 */
void PwmOut::write(float duty_cycle)
{
	this->duty_cycle = CppUtil::clamp(duty_cycle, 0.0f, 1.0f);
	analogWrite(pin, this->duty_cycle * 255.0f);
}

/**
 * @brief Returns current duty cycle
 */
float PwmOut::read()
{
	return duty_cycle;
}

/**
 * @brief Shorthand for write operation
 * @param duty_cycle Duty cycle in range [0,1]
 */
PwmOut& PwmOut::operator=(float duty_cycle)
{
	write(duty_cycle);
	return *this;
}

/**
 * @brief Shorthand for read operation
 */
PwmOut::operator float()
{
	return read();
}

#endif
