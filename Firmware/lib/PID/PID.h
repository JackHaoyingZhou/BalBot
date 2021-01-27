/**
 * @file PID.h
 * @brief Class for implementing discrete-time PID controllers
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once

class PID
{
public:
	PID(float k_p, float k_i, float k_d, float u_min, float u_max, float f_ctrl);
	PID();
	void set_gains(float k_p, float ki, float kd);
	void set_k_p(float k_p);
	void set_k_i(float k_i);
	void set_k_d(float k_d);
	void set_limits(float u_min, float u_max);
	void set_u_min(float u_min);
	void set_u_max(float u_max);
	float update(float error, float ff = 0.0f, bool sat = false);
	void reset();
private:
	float k_p, k_i, k_d, u_min, u_max, f_ctrl, t_ctrl;
	float u, u_p, u_i, u_d;
	float error_prev;
	bool first_frame;
};
