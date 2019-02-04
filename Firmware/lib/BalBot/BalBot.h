/**
 * @file BalBot.h
 * @brief Contains all BalBot constants.
 */
#pragma once

// Robot Physical Constants
const float r_wheel = 0.0336;	// Wheel radius [m]
const float motor_kv = 0.3f;	// Motor back-EMF [V/(rad/s)] 
const float v_bat = 12.0f;		// Battery voltage [V]

// Controller Constants
const float f_ctrl = 200.0f;			// Control frequency [Hz]
const float t_ctrl = 1.0f / f_ctrl;		// Control period [s]
const float pid_pitch_kp = 32.77f;		// Pitch P-gain [V/rad]
const float pid_pitch_ki = 0.0f;		// Pitch I-gain [V/(rad*s)]
const float pid_pitch_kd = 1.947f;		// Pitch D-gain [V/(rad/s)]
const float pitch_max = 0.1f;			// Max pitch command [rad]
const float pid_pos_kp = 1.0;			// Position P-gain [rad/m]
const float pid_pos_ki = 0.0f;			// Position I-gain [rad/(m*s)]
const float pid_pos_kd = 0.1f;			// Position D-gain [rad/(m/s)]

// Encoder Constants
const float encoder_cpr = 1320.0f;	// Counts per revolution