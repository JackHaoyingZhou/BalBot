/**
 * @file Mpu6050.h
 * @brief Class for interfacing with MPU-6050 IMU.
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <Arduino.h>
#include <I2CDevice.h>

class Mpu6050
{
public:

	// Constructor
	Mpu6050(TwoWire* wire = &Wire);
	void init();

	// Calibration
	void calibrate(float num_samples = 100);
	void set_gyro_cals(float vel_x_cal, float vel_y_cal, float vel_z_cal);
	float get_vel_x_cal();
	float get_vel_y_cal();
	float get_vel_z_cal();
	float get_vel_variance();
	float get_acc_variance();

	// Reading Retrieval
	void update();
	float get_vel_x();
	float get_vel_y();
	float get_vel_z();
	float get_acc_x();
	float get_acc_y();
	float get_acc_z();

private:

	// I2C Registers
	static const uint8_t i2c_addr = 0x68;
	static const uint8_t reg_pwrmgmt_addr = 0x6B;
	static const uint8_t reg_pwrmgmt_wake = 0x00;
	static const uint8_t reg_data_addr = 0x3B;

	// Unit Conversions
	static const float vel_per_cnt;
	static const float acc_per_cnt;

	// Class Members
	I2CDevice i2c_device;
	float vel_x, vel_y, vel_z;
	float acc_x, acc_y, acc_z;
	float vel_x_cal, vel_y_cal, vel_z_cal;
	float vel_var, acc_var;
};