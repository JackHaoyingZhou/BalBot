/**
 * @file DigitalIn.h
 * @brief Class for Arduino and Mbed digital inputs
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <Platform.h>

#if defined(PLATFORM_ARDUINO)

/**
 * PinMode Enumeration
 */
typedef enum
{
	PullUp,
	PullNone,
}
PinMode;

/**
 * Class Declaration
 */
class DigitalIn
{
public:
	DigitalIn(Platform::pin_t pin, PinMode mode = PullNone);
	int read();
	void mode(PinMode mode);
	int is_connected();
	operator int();
protected:
	Platform::pin_t pin;
};

#endif
