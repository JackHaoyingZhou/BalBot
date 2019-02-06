/**
 * @file Imu.h
 * @brief Namespace for BalBot IMU interface.
 * @author Dan Oates (WPI Class of 2020)
 */
#include <Mpu6050.h>

namespace Imu
{
	extern Mpu6050 imu;
	void init();
	void update();
	float get_pitch();
	float get_yaw_vel();
}