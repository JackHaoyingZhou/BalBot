/**
 * @file ClampLimiter.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "ClampLimiter.h"
#include <CppUtil.h>

/**
 * @brief Constructs clamp limiter
 * @param val_min Minimum output
 * @param val_max Maximum output
 */
ClampLimiter::ClampLimiter(float val_min, float val_max)
{
	set_min(val_min);
	set_max(val_max);
}

/**
 * Constructs symmetric clamp limiter
 * @param val_max Maximum positive-negative output
 */
ClampLimiter::ClampLimiter(float val_max) :
	ClampLimiter(-val_max, val_max)
{
	return;
}

/**
 * @return Minimum output
 */
float ClampLimiter::get_min()
{
	return val_min;
}

/**
 * @return Maximum output
 */
float ClampLimiter::get_max()
{
	return val_max;
}

/**
 * @brief Sets minimum output
 */
void ClampLimiter::set_min(float val)
{
	this->val_min = val;
}

/**
 * @brief Sets maximum output
 */
void ClampLimiter::set_max(float val)
{
	this->val_max = val;
}

/**
 * @brief Updates filter with new value
 * @param val Input valut
 * @return Clamped output value
 */
float ClampLimiter::update(float val)
{
	return CppUtil::clamp(val, val_min, val_max);
}
