/**
 * @file Imu.h
 * @brief IMU-based state estimation subsystem.
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once

namespace Imu
{
	void init();
	void update();
	float get_pitch();
	float get_pitch_vel();
	float get_yaw_vel();
	void calibrate();
}