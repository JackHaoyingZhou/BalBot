/**
 * @file Timer.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "Timer.h"

#if defined(PLATFORM_ARDUINO)

/**
 * @brief Initializes and stops timer.
 */
Timer::Timer()
{
	running = false;
	reset();
}

/**
 * @brief Starts timer
 */
void Timer::start()
{
	if (!running)
	{
		start_time_us += micros() - stop_time_us;
		running = true;
	}
}

/**
 * @brief Stops timer
 */
void Timer::stop()
{
	if (running)
	{
		stop_time_us = micros();
		running = false;
	}
}

/**
 * @brief Resets timer
 */
void Timer::reset()
{
	start_time_us = micros();
	if (running)
	{
		stop_time_us = 0;
	}
	else
	{
		stop_time_us = start_time_us;
	}
}

/**
 * @brief Returns time in seconds
 */
float Timer::read()
{
	return read_us() * 0.000001f;
}

/**
 * @brief Returns time in milliseconds
 */
uint32_t Timer::read_ms()
{
	return read_us() / 1000;
}

/**
 * @brief Returns time in microseconds
 */
uint32_t Timer::read_us()
{
	if (running)
	{
		return micros() - start_time_us;
	}
	else
	{
		return stop_time_us - start_time_us;
	}
}

/**
 * @brief Shorthand for read in seconds
 */
Timer::operator float()
{
	return read();
}

#endif
