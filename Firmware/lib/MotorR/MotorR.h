/**
 * @file MotorR.h
 * @brief Namespace for BalBot right drive motor.
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once

namespace MotorR
{
	void init();
	void update();
	void set_voltage(float v_cmd);
	float get_angle();
	float get_velocity();
}