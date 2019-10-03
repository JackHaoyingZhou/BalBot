/**
 * @file MotorConfig.h
 * @brief Namespace for robot-specific motor configuration constants.
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once

namespace MotorConfig
{
	const extern float direction;	// Motor direction (+1 for regular, -1 for reversed)
	const extern float cnt_per_rev;	// Encoder counts per revolution
}