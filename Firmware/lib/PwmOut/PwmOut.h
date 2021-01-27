/**
 * @brief PwmOut.h
 * @brief Class for Arduino and Mbed PWM outputs
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <Platform.h>

#if defined(PLATFORM_ARDUINO)

/**
 * Class Declaration
 */
class PwmOut
{
public:
	PwmOut(Platform::pin_t pin);
	void write(float duty_cycle);
	float read();
	PwmOut& operator=(float duty_cycle);
	operator float();
protected:
	Platform::pin_t pin;
	float duty_cycle;
};

#endif
