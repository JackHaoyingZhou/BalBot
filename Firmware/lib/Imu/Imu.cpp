/**
 * @file Imu.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "Imu.h"
#include <BalBot.h>
#include <Gaussian.h>

#include <Arduino.h>

namespace Imu
{
	// IMU Hardware Interface
	Mpu6050 imu;

	// IMU Constants
	const float vel_x_cal = -0.0767443330f;		// Gyro x calibration offset [rad/s]
	const float vel_y_cal = +0.0393428880f;		// Gyro y calibration offset [rad/s]
	const float vel_z_cal = +0.0022024342f;		// Gyro z calibration offset [rad/s]
	const float vel_var = 0.0000035204512f;		// Angular velocity variance [(rad/s)^2]
	const float acc_var = 0.0012492317000f;		// Acceleration variance [(m/s^2)^2]

	// State Variables
	bool first_frame = true;
	Gaussian pitch;
}

/**
 * @brief Initializes and calibrates IMU.
 */
void Imu::init()
{
	imu.init();
	imu.set_gyro_cals(vel_x_cal, vel_y_cal, vel_z_cal);
}

/**
 * @brief Reads IMU and updates state estimates.
 */
void Imu::update()
{
	imu.update();
	const Gaussian acc_y(imu.get_acc_y(), acc_var);		// Y-acceleration [m/s^2]
	const Gaussian acc_z(imu.get_acc_z(), acc_var);		// Z-acceleration [m/s^2]
	const Gaussian pitch_acc = -atan2(acc_y, acc_z);	// Accelerometer pitch estimate [rad]
	if(first_frame)
	{
		first_frame = false;	// Reset first frame flag
		pitch = pitch_acc;		// Ignore gyro on first frame
	}
	else
	{
		const Gaussian pitch_vel(-imu.get_vel_x(), vel_var);	// Gyro pitch velocity [rad/s]
		const Gaussian pitch_gyr = pitch + pitch_vel * t_ctrl;	// Gyro pitch estimate [rad]
		pitch = fuse(pitch_gyr, pitch_acc);						// Fused pitch estimate [rad]
	}
}

/**
 * @brief Returns IMU pitch estimate computed via Kalman filter.
 */
float Imu::get_pitch()
{
	return pitch.get_mean();
}