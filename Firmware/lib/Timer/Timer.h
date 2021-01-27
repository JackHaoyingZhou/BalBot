/**
 * @file Timer.h
 * @brief Class for Arduino and Mbed event timing
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <Platform.h>

#if defined(PLATFORM_ARDUINO)

/**
 * Class Declaration
 */
class Timer
{
public:
	Timer();
	void start();
	void stop();
	void reset();
	float read();
	uint32_t read_ms();
	uint32_t read_us();
	operator float();
protected:
	uint32_t start_time_us;
	uint32_t stop_time_us;
	bool running;
};

#endif
