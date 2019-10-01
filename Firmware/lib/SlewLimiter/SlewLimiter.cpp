/**
 * @file SlewLimiter.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "SlewLimiter.h"
#include <CppUtil.h>

/**
 * @brief Constructs assymetric slew limiter.
 * @param rate_max Maximum rate of change [U/T]
 * @param rate_min Minimum rate of change [U/T]
 * @param f_sample Sample rate [1/T]
 */
SlewLimiter::SlewLimiter(float rate_max, float rate_min, float f_sample)
{
	float t_sample = 1.0f / f_sample;
	this->delta_max = rate_max * t_sample;
	this->delta_min = rate_min * t_sample;
	val_prev = 0.0f;
	first_frame = true;
}

/**
 * @brief Constructs symmetric slew limiter.
 * @param rate_max Maximum bidirectional rate of change [U/T]
 * @param f_sample Sample rate [1/T]
 */
SlewLimiter::SlewLimiter(float rate_max, float f_sample) :
	SlewLimiter(rate_max, -rate_max, f_sample)
{
	return;
}

/**
 * @brief Applies slew limit to given value.
 * @param val Input value.
 * @return Slew-limited value.
 */
float SlewLimiter::update(float val)
{
	float val_slew;
	if(first_frame)
	{
		val_slew = val;
		first_frame = false;
	}
	else
	{
		float delta = val - val_prev;
		delta = clamp_limit(delta, delta_min, delta_max);
		val_slew = val_prev + delta;
	}
	val_prev = val_slew;
	return val_slew;
}

/**
 * @brief Resets slew limiter.
 */
void SlewLimiter::reset()
{
	first_frame = true;
}