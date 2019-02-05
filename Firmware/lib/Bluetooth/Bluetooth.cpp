/**
 * @file Bluetooth.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "Bluetooth.h"
#include <BalBot.h>
#include <Controller.h>
#include <SerialComms.h>

namespace Bluetooth
{
	// Hardware interfaces
	SerialComms comms(Serial);

	// Received commands
	float vel_cmd = 0.0f;	// Linear velocity [m/s]
	float yaw_cmd = 0.0f;	// Yaw velocity [rad/s]
}

/**
 * @brief Initializes Bluetooth module and serial.
 */
void Bluetooth::init()
{
	comms.init(serial_baud);
	comms.flush();
}

/**
 * @brief Checks Bluetooth serial buffer for commands.
 */
void Bluetooth::update()
{
	if(comms.available() >= 8)
	{
		vel_cmd = comms.read_float();
		yaw_cmd = comms.read_float();
		comms.write_float(Controller::get_lin_vel());
		comms.write_float(Controller::get_yaw_vel());
		comms.write_float(Controller::get_motor_L_cmd());
		comms.write_float(Controller::get_motor_R_cmd());
	}
}

/**
 * @brief Returns linear velocity command [m/s].
 */
float Bluetooth::get_vel_cmd()
{
	return vel_cmd;
}

/**
 * @brief Returns yaw velocity command [rad/s].
 */
float Bluetooth::get_yaw_cmd()
{
	return yaw_cmd;
}