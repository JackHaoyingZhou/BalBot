/**
 * @file DigitalOut.h
 * @brief Class for Arduino and Mbed digital outputs
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <Platform.h>

#if defined(PLATFORM_ARDUINO)

/**
 * Class Declaration
 */
class DigitalOut
{
public:
	DigitalOut(Platform::pin_t pin, int value = 0);
	void write(int value);
	int read();
	int is_connected();
	DigitalOut& operator=(int value);
	operator int();
protected:
	Platform::pin_t pin;
	int value;
};

#endif
