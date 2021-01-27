/**
 * @file ClampLimiter.h
 * @brief Class for clamp-limiting (saturating) signals
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <stdint.h>

/**
 * Class Declaration
 */
class ClampLimiter
{
public:
	ClampLimiter(float val_min, float val_max);
	ClampLimiter(float val_max);
	float get_min();
	float get_max();
	void set_min(float val);
	void set_max(float val);
	float update(float val);
protected:
	float val_min;
	float val_max;
};
