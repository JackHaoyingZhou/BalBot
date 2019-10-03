/**
 * @file Imu.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "Imu.h"
#include <ImuConfig.h>
#include <BalBot.h>
#include <Gaussian.h>
#include <Mpu6050.h>

namespace Imu
{
	// IMU Hardware Interface
	Mpu6050 imu;

	// State Variables
	bool first_frame = true;
	Gaussian pitch;
	Gaussian pitch_vel;
	float yaw_vel;
}

/**
 * @brief Initializes and calibrates IMU.
 */
void Imu::init()
{
	imu.init();
	imu.set_gyro_cals(
		ImuConfig::vel_x_cal,
		ImuConfig::vel_y_cal,
		ImuConfig::vel_z_cal);
}

/**
 * @brief Reads IMU and updates state estimates.
 */
void Imu::update()
{
	// Get new readings from IMU
	imu.update();

	// Pitch estimation Kalman Filter
	const Gaussian acc_y(imu.get_acc_y(), ImuConfig::acc_var);	// Y-acceleration [m/s^2]
	const Gaussian acc_z(imu.get_acc_z(), ImuConfig::acc_var);	// Z-acceleration [m/s^2]
	const Gaussian pitch_acc = atan2(acc_y, acc_z);				// Accelerometer pitch estimate [rad]
	pitch_vel = Gaussian(imu.get_vel_x(), ImuConfig::vel_var);	// Gyro pitch velocity [rad/s]
	if(first_frame)
	{
		first_frame = false;	// Reset first frame flag
		pitch = pitch_acc;		// Ignore gyro on first frame
	}
	else
	{
		const Gaussian pitch_gyr = pitch + pitch_vel * t_ctrl;	// Gyro pitch estimate [rad]
		pitch = fuse(pitch_gyr, pitch_acc);						// Fused pitch estimate [rad]
	}

	// Yaw velocity estimation
	yaw_vel =
		imu.get_vel_z() * cosf(pitch.get_mean()) +
		imu.get_vel_y() * sinf(pitch.get_mean());
}

/**
 * @brief Returns IMU pitch estimate computed via Kalman filter.
 */
float Imu::get_pitch()
{
	return pitch.get_mean();
}

/**
 * @brief Returns IMU pitch velocity measurement.
 */
float Imu::get_pitch_vel()
{
	return pitch_vel.get_mean();
}

/**
 * @brief Returns IMU yaw velocity estimate.
 */
float Imu::get_yaw_vel()
{
	return yaw_vel;
}

/**
 * @brief Calibrates IMU and prints values to Serial.
 */
void Imu::calibrate()
{
	imu.calibrate();
	Serial.println("IMU Calibration Code:");
	Serial.println("Gyro x: " + String(imu.get_vel_x_cal(), 20) + " [rad/s]");
	Serial.println("Gyro y: " + String(imu.get_vel_y_cal(), 20) + " [rad/s]");
	Serial.println("Gyro z: " + String(imu.get_vel_z_cal(), 20) + " [rad/s]");
	Serial.println("Acc Var: " + String(imu.get_acc_variance(), 20) + " [(m/s^2)^2]");
	Serial.println("Vel Var: " + String(imu.get_vel_variance(), 20) + " [(rad/s)^2]");
}