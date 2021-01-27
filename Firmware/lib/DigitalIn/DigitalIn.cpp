/**
 * @file DigitalIn.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "DigitalIn.h"

#if defined(PLATFORM_ARDUINO)

/**
 * @brief Constructs digital input
 * @param pin Platform-specific pin ID
 * @param pull Pin mode (PullUp, PullNone)
 */
DigitalIn::DigitalIn(Platform::pin_t pin, PinMode pull)
{
	this->pin = pin;
	mode(pull);
}

/**
 * @brief Reads digital input
 * @return 1 if high, 0 if low
 */
int DigitalIn::read()
{
	return digitalRead(pin);
}

/**
 * @brief Sets pin mode
 * @param pull Pin mode (PullUp, PullNone)
 */
void DigitalIn::mode(PinMode pull)
{
	switch (pull)
	{
		case PullUp:
			pinMode(pin, INPUT_PULLUP);
			break;
		case PullNone:
			pinMode(pin, INPUT);
			break;
	}
}

/**
 * @brief Returns 1 if object is connected to input
 * 
 * Note: For Arduino, this always returns 1.
 */
int DigitalIn::is_connected()
{
	return 1;
}

/**
 * @brief Shorthand for reading input
 * @return 1 if high, 0 if low
 */
DigitalIn::operator int()
{
	return read();
}

#endif
