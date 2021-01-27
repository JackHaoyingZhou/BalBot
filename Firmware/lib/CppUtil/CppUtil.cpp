/**
 * @file CppUtil.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "CppUtil.h"

/**
 * @brief Wrap (modulo) limits x to range [x_min, x_max]
 */
float CppUtil::wrap(float x, float x_min, float x_max)
{
	return
	    x > x_max ? fmodf(x - x_min, x_max - x_min) + x_min :
	    x < x_min ? fmodf(x - x_min, x_max - x_min) - x_max : x;
}
