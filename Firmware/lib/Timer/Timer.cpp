/**
 * @file Timer.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "Timer.h"

/**
 * @brief Constructs timer.
 */
Timer::Timer()
{
	start_time = 0;
}

/**
 * @brief Starts (or resets) timer.
 */
void Timer::tic()
{
	start_time = micros();
}

/**
 * @brief Returns time in seconds since last 'tic'.
 */
float Timer::toc()
{
	return (micros() - start_time) * 0.000001f;
}

/**
 * @brief Determines if given time has elapsed since last 'tic'.
 * @param t Elapsed time check (s)
 */
bool Timer::has_elapsed(float t)
{
	return (toc() >= t);
}

/**
 * @brief Pauses program until given time has elapsed since last 'tic'.
 * @param t Elapsed time check (s).
 */
void Timer::wait_until(float t) {
	uint32_t end_time = start_time + t * 1000000.0f;
	while(micros() < end_time);
}

/**
 * @brief Returns time since program start in seconds.
 * Accurate to 1us. Will overflow after about 1.2 hours.
 */
float clock_time()
{
	return micros() * 0.000001;
}

/**
 * @brief Pauses program for given number of seconds.
 * Imprecise, does not account for floating-point multiply.
 * Will overflow after about 7 weeks.
 */
void delay_seconds(float t)
{
	delay(t * 1000.0f);
}