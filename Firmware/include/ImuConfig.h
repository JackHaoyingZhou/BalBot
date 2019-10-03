/**
 * @file ImuConfig.h
 * @brief Namespace for robot-specific IMU calibration constants.
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once

namespace ImuConfig
{
	const extern float vel_x_cal;	// Gyro x offset [rad/s]
	const extern float vel_y_cal;	// Gyro y offset [rad/s]
	const extern float vel_z_cal;	// Gyro z offset [rad/s]
	const extern float vel_var;		// Gyro variance [(rad/s)^2]
	const extern float acc_var;		// Accelerometer variance [(m/s^2)^2]
}