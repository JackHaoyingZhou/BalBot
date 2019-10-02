/**
 * @file Imu.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "Imu.h"
#include <BalBot.h>
#include <Gaussian.h>
#include <Mpu6050.h>

namespace Imu
{
	// IMU Hardware Interface
	Mpu6050 imu;

	/**
	 * IMU Constants
	 * vel_x_cal = Gyro x calibration offset [rad/s]
	 * vel_y_cal = Gyro y calibration offset [rad/s]
	 * vel_z_cal = Gyro z calibration offset [rad/s]
	 * vel_var = Angular velocity variance [(rad/s)^2]
	 * acc_var = Acceleration variance [(m/s^2)^2]
	 */
#if ES3011_BOT_ID == 0
	const float vel_x_cal = -0.0767443330f;
	const float vel_y_cal = +0.0393428880f;
	const float vel_z_cal = +0.0022024342f;
	const float vel_var = 0.0000035204512f;
	const float acc_var = 0.0012492317000f;
#elif ES3011_BOT_ID == 1
	const float vel_x_cal = +0.0311310290f;
	const float vel_y_cal = +0.0018575554f;
	const float vel_z_cal = -0.0121866260f;
	const float vel_var = 0.0000074203535f;
	const float acc_var = 0.0006528628300f;
#elif ES3011_BOT_ID == 2
	const float vel_x_cal = -0.0138670760f;
	const float vel_y_cal = -0.0743288400f;
	const float vel_z_cal = -0.0213452480f;
	const float vel_var = 0.0000040159848f;
	const float acc_var = 0.0010868423000f;
#elif ES3011_BOT_ID == 3
#elif ES3011_BOT_ID == 4
#elif ES3011_BOT_ID == 5
#elif ES3011_BOT_ID == 6
#elif ES3011_BOT_ID == 7
#elif ES3011_BOT_ID == 8
#elif ES3011_BOT_ID == 9
#elif ES3011_BOT_ID == 10
#elif ES3011_BOT_ID == 11
#elif ES3011_BOT_ID == 12
#elif ES3011_BOT_ID == 13
#elif ES3011_BOT_ID == 14
#elif ES3011_BOT_ID == 15
#elif ES3011_BOT_ID == 16
#elif ES3011_BOT_ID == 17
#elif ES3011_BOT_ID == 18
#elif ES3011_BOT_ID == 19
#elif ES3011_BOT_ID == 20
#else
#error Must define ES3011_BOT_ID in range [0, 20]
#endif

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
	imu.set_gyro_cals(vel_x_cal, vel_y_cal, vel_z_cal);
}

/**
 * @brief Reads IMU and updates state estimates.
 */
void Imu::update()
{
	// Get new readings from IMU
	imu.update();

	// Pitch estimation Kalman Filter
	const Gaussian acc_y(imu.get_acc_y(), acc_var);	// Y-acceleration [m/s^2]
	const Gaussian acc_z(imu.get_acc_z(), acc_var);	// Z-acceleration [m/s^2]
	const Gaussian pitch_acc = atan2(acc_y, acc_z);	// Accelerometer pitch estimate [rad]
	pitch_vel = Gaussian(imu.get_vel_x(), vel_var);	// Gyro pitch velocity [rad/s]
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