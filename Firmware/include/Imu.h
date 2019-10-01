/**
 * @file Imu.h
 * @brief Namespace for BalBot IMU interface.
 * @author Dan Oates (WPI Class of 2020)
 */

namespace Imu
{
	void init();
	void update();
	float get_pitch();
	float get_pitch_vel();
	float get_yaw_vel();
	void calibrate();
}