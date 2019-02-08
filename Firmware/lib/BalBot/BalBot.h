/**
 * @file BalBot.h
 * @brief Contains all BalBot constants.
 */
#pragma once
#include <Arduino.h>

// Robot Physical Constants
const float Ix = 0.00314f;	// Pitch inertia [kg*m^2]
const float Iz = 0.00150f;	// Yaw inertia [kg*m^2]
const float m = 0.956f;		// Robot mass [kg]
const float g = 9.81;		// Gravity [m/s^2]
const float dG = 0.033f;	// CG distance [m]
const float dB = 0.171;		// Wheel base [m]
const float Rw = 0.0336;	// Wheel radius [m]
const float Rm = 5.4f;		// Motor resistance [Ohm]
const float Kv = 0.34f;		// Motor back-EMF [V/(rad/s)]
const float Kt = 0.20f;		// Motor torque [N*m/A]
const float Vb = 12.0f;		// Battery voltage [V]

// Controller Constantsz
const float f_ctrl = 100.0f;	// Control frequency [Hz]
const float yaw_kp = 0.0f;		// Yaw P-gain [V/(rad/s)]
const float yaw_ki = 10.0f;		// Yaw I-gain [V/rad]
const float yaw_kd = 0.0f;		// Yaw D-gain [V/(rad/s^2)]
const float ss_K1 = -1.97f;		// SS K1 [V/(rad/s)]
const float ss_K2 = -19.6f;		// SS K2 [V/rad]
const float ss_K3 = -16.0f;		// SS K3 [V/(m/s)]
const float yaw_max = 1.6f;		// Yaw velocity limit [rad/s]
const float vel_max = 0.8f;		// Velocity limit [m/s]
const float acc_max = 0.8f;		// Acceleration limit [m/s^2]

// Derived Constants
const float Kv_div_Rw = Kv / Rw;	// Velocity back-EMF [V/(m/s)]
const float t_ctrl = 1.0f / f_ctrl;	// Control period [s]
const float dB_inv = 1.0f / dB;		// Wheel base inverse [1/m]
const float Rw_div_2 = Rw / 2.0f;	// Half wheel radius [m]

// Encoder Resolution [cnt/rev]
const float encoder_cpr = 1320.0f;

// Serial Baud Rate [bit/s]
const uint32_t serial_baud = 57600;