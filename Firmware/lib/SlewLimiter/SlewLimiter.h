/**
 * @file SlewLimiter.h
 * @brief Class for implementing asymmetric slew limiting.
 * @author Dan Oates (WPI Class of 2020)
 * 
 * This class is used for limiting the rate of change of a 
 * value with units 'U' with respect to a time unit 'T'. It
 * assumes a constant sample rate provided in the constructor.
 * Rate limits should be given in units of [U/T] and the
 * sample rate should be given in units of [1/T].
 * 
 * For example, if slew limiting a temperature setpoint in
 * units of [degF / minute], the sample rate should be provided
 * in units of [samples / minute].
 * 
 * On the first frame after construction or reset, the input
 * is assigned directly to the output.
 */
#pragma once

class SlewLimiter
{
public:
	SlewLimiter(float rate_max, float rate_min, float f_sample);
	SlewLimiter(float rate_max, float f_sample);
	float update(float val);
	void reset();
private:
	bool first_frame;
	float val_prev;
	float delta_max;
	float delta_min;
};