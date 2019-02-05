/**
 * @file BalBot.h
 * @brief Contains all BalBot constants.
 */
#pragma once
#include <Arduino.h>

// Robot Physical Constants
const float wheel_radius = 0.0336;	// Wheel radius [m]
const float wheel_base = 0.171;		// Wheel base [m]
const float motor_kv = 0.3f;		// Motor back-EMF [V/(rad/s)] 
const float v_bat = 12.0f;			// Battery voltage [V]

// Controller Constants
const float f_ctrl = 100.0f;			// Control frequency [Hz]
const float pid_pitch_kp = 32.77f;		// Pitch P-gain [V/rad]
const float pid_pitch_ki = 0.0f;		// Pitch I-gain [V/(rad*s)]
const float pid_pitch_kd = 1.947f;		// Pitch D-gain [V/(rad/s)]
const float pitch_max = 0.1f;			// Max pitch command [rad]

// Encoder Resolution [cnt/rev]
const float encoder_cpr = 1320.0f;

// Serial Baud Rate [bit/s]
const uint32_t serial_baud = 57600;

// Derived constants
const float t_ctrl = 1.0f / f_ctrl;
const float wheel_base_inv = 1.0f / wheel_base;
const float open_loop_yaw_gain =	// Yaw gain [V/(rad/s)]
	motor_kv * wheel_base / (2.0f * wheel_radius);
const float open_loop_vel_gain = 
	motor_kv / wheel_radius;