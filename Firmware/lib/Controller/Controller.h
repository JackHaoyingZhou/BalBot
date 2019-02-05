/**
 * @file Controller.h
 * @brief Pitch and velocity control system for BalBot.
 * @author Dan Oates (WPI Class of 2020).
 */
#pragma once

namespace Controller
{
	void update();
	float get_lin_vel();
	float get_yaw_vel();
	float get_motor_L_cmd();
	float get_motor_R_cmd();
}