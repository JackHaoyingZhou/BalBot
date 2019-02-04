/**
 * @file PinDefs.h
 * @brief Contains Arduino pin definitions for BalBot hardware interfaces.
 * @author Dan Oates (WPI Class of 2020)
 * @see https://www.sparkfun.com/products/14451
 */
#pragma once
#include <Arduino.h>

// Motor Driver Enable (TB6612FNG)
const uint8_t pin_motor_en = 8;

// Left Motor Control (H-Bridge)
const uint8_t pin_lm_pwm = 9;	// PWM
const uint8_t pin_lm_fwd = 6;	// Forward enable
const uint8_t pin_lm_rev = 7;	// Reverse enable

// Right Motor Control (H-Bridge)
const uint8_t pin_rm_pwm = 10;	// PWM
const uint8_t pin_rm_fwd = 12;	// Forward enable
const uint8_t pin_rm_rev = 13;	// Reverse enable

// Encoder Interrupts (Quadrature)
const uint8_t pin_lenc_a = 2;	// Left A
const uint8_t pin_lenc_b = 3;	// Left B
const uint8_t pin_renc_a = 5;	// Right A
const uint8_t pin_renc_b = 4;	// Right B