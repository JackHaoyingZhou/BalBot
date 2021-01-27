/**
 * @file PID.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "PID.h"
#include <CppUtil.h>
using CppUtil::clamp;

/**
 * @brief Constructor for PID controller
 * @param k_p Proportional gain
 * @param k_i Integral gain
 * @param k_d Derivative gain
 * @param u_min Minimum response
 * @param u_max Maximum response
 * @param f_ctrl Control frequency
 */
PID::PID(float k_p, float k_i, float k_d, float u_min, float u_max, float f_ctrl)
{
	this->f_ctrl = f_ctrl;
	this->t_ctrl = 1.0f / f_ctrl;
	set_gains(k_p, k_i, k_d);
	set_limits(u_min, u_max);
	reset();
}

/**
 * @brief Default constructor for PID controller
 * 
 * Note: For array instantiation only
 */
PID::PID() : PID(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)
{
	return;
}

/**
 * @brief Updates PID gains
 * @param k_p Proportional gain
 * @param k_i Integral gain
 * @param k_d Derivative gain
 */
void PID::set_gains(float k_p, float k_i, float k_d)
{
	set_k_p(k_p);
	set_k_i(k_i);
	set_k_d(k_d);
}

/**
 * @brief Updates P-gain
 * @param k_p Proportional gain
 */
void PID::set_k_p(float k_p)
{
	this->k_p = k_p;
}

/**
 * @brief Updates I-gain
 * @param k_i Integral gain
 */
void PID::set_k_i(float k_i)
{
	this->k_i = k_i * t_ctrl;
}

/**
 * @brief Updates D-gain
 * @param k_d Derivative gain
 */
void PID::set_k_d(float k_d)
{
	this->k_d = k_d * f_ctrl;
}

/**
 * @brief Updates response limits
 * @param u_min Minimum response
 * @param u_max Maximum response
 */
void PID::set_limits(float u_min, float u_max)
{
	set_u_max(u_max);
	set_u_min(u_min);
}

/**
 * @brief Updates minimum response
 * @param u_min Minimum response
 */
void PID::set_u_min(float u_min)
{
	this->u_min = u_min;
}

/**
 * @brief Updates maximum response
 * @param u_max Maximum response
 */
void PID::set_u_max(float u_max)
{
	this->u_max = u_max;
}

/**
 * @brief Calculates response to given error
 * @param error Setpoint error
 * @param ff Feed-forward term (optional)
 * @param sat = Saturation flag (optional)
 */
float PID::update(float error, float ff, bool sat)
{
	// P-control
	u_p = k_p * error;

	// I-control
	bool int_pos = (error > 0.0f && u < u_max);
	bool int_neg = (error < 0.0f && u > u_min);
	if ((int_pos || int_neg) && !sat)
	{
		u_i += k_i * error;
	}

	// D-control
	if (first_frame)
	{
		u_d = 0.0f;
		first_frame = false;
	}
	else
	{
		float error_diff = error - error_prev;
		u_d = k_d * error_diff;
	}
	error_prev = error;

	// Combine
	u = clamp(u_p + u_i + u_d + ff, u_min, u_max);
	return u;
}

/**
 * @brief Resets PID controller (zeros derivative and integral terms)
 */
void PID::reset()
{
	u = 0.0f;
	u_p = 0.0f;
	u_i = 0.0f;
	u_d = 0.0f;
	error_prev = 0.0f;
	first_frame = true;
}
