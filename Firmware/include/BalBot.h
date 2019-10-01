/**
 * @file BalBot.h
 * @brief Contains all BalBot constants.
 */
#pragma once
#include <Arduino.h>

// Robot Physical Constants
const float Ix = 0.00215f;	// Pitch inertia [kg*m^2]
const float Iz = 0.00110f;	// Yaw inertia [kg*m^2]
const float m = 0.955f;		// Robot mass [kg]
const float g = 9.81f;		// Gravity [m/s^2]
const float dg = 0.062f;	// CG height [m]
const float dw = 0.085f;	// Wheel to CG Z-axis [m]
const float dr = 0.034;		// Wheel radius [m]
const float R = 5.4f;		// Motor resistance [Ohm]
const float Kv = 0.34f;		// Back-EMF constant [V/(rad/s)]
const float Kt = 0.20f;		// Torque constant [N*m/A]
const float Vb = 12.0f;		// Battery voltage [V]

// Derived Physical Constants
const float Mx = Ix*dr/dg;	// Generalized X-mass [kg*m^2]
const float My = m*dr;		// Generalized Y-mass [kg*m]
const float Mz = Iz*dr/dw;	// Generalized Z-mass [kg*m^2]
const float Tg = m*g*dr;	// Gravitational torque [N*m]
const float Gt = 2.0f*Kt/R;	// Torque-voltage gain [N*m/V]
const float Gv = Kv/dr;		// Linear back-EMF [V/(m/s)]
const float Gw = Kv*dw/dr;	// Yaw back-EMF [V/(rad/s)]

// Controller Constants
const float f_ctrl = 100.0f;	// Control frequency [Hz]
const float pitch_max = 0.5f;	// Max pitch angle [rad]
const float yaw_max = 1.6f;		// Yaw velocity limit [rad/s]
const float vel_max = 0.8f;		// Velocity limit [m/s]
const float acc_max = 0.8f;		// Acceleration limit [m/s^2]
const float px = 20.0f;			// Pitch-velocity pole [1/s]
const float pz = 80.0f;			// Yaw velocity pole [1/s]

// Derived Controller Constants
const float dr_div_2 = dr/2.0f;		// Half wheel radius [m]
const float t_ctrl = 1.0f/f_ctrl;	// Control period [s]

// Pitch-Velocity State-Space Gains
const float ss_K1 = Mx*Mx/(Gt*Tg)*px*px*px + 3.0f*Mx/Gt*px;
const float ss_K2 = 3.0f*Mx/Gt*px*px + Tg/Gt;
const float ss_K3 = -Mx*My/(Gt*Tg)*px*px*px - Gv;

// Yaw Velocity PI-Controller Gains
const float yaw_Kp = 0.0f;
const float yaw_Ki = 5.0f;
const float yaw_Kd = 0.0f;
/** Analytical Gains
const float yaw_Kp = (2*Mz/Gt)*pz - Gw;
const float yaw_Ki = (Mz/Gt)*pz*pz;
const float yaw_Kd = 0.0f;
*/

// Encoder Resolution [cnt/rev]
const float encoder_cpr = 1320.0f;

// Serial Baud Rate [bit/s]
const uint32_t serial_baud = 57600;