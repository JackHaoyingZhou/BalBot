/**
 * @file SlewLimiter.h
 * @brief Class for implementing asymmetric slew limiting
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <ClampLimiter.h>

class SlewLimiter
{
public:
	SlewLimiter(float rate_max, float rate_min, float f_sample);
	SlewLimiter(float rate_max, float f_sample);
	void set_min(float rate);
	void set_max(float rate);
	float update(float val);
	void reset();
private:
	ClampLimiter delta_limiter;
	bool first_frame;
	float t_sample;
	float val_prev;
};
