/**
 * @file Bluetooth.h
 * @brief Bluetooth communication subsystem.
 * @author Dan Oates (WPI Class of 2020)
 */

namespace Bluetooth
{
	void init();
	void update();
	float get_vel_cmd();
	float get_yaw_cmd();
}