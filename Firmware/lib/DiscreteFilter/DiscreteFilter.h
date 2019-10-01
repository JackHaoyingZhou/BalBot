/**
 * @file DiscreteFilter.h
 * @brief Class for implementing linear discrete-time filters.
 * @author Dan Oates (WPI Class of 2020)
 * @see https://en.wikipedia.org/wiki/Digital_filter
 * 
 * This class implements the following difference equation:
 * 
 * a[0] * y[n] + a[1] * y[n-1] + ... + a[A-1] * y[n-(A-1)] =
 * b[0] * x[n] + b[1] * x[n-1] + ... + b[B-1] * x[n-(B-1)]
 * 
 * Where y[n] and x[n] are zero for n < 0. After initialization
 * or reset, the filters output 0 until all past inputs x[n] to
 * x[n-(B-1)] are populated.
 * 
 * This library contains functions to making four basic first-
 * order filters:
 * 
 * - Low-pass filter
 * - High-pass filter
 * - Differentiator
 * - Integrator
 * 
 * This library avoids dynamic memory for variable-size filters
 * by pre-allocating fixed-size arrays for every instance. The
 * maximum sizes are defined by the following two macros:
 * 
 * DISCRETE_FILTER_MAX_A : Maximum value of A (>= 2)
 * DISCRETE_FILTER_MAX_B : Maximum value of B (>= 2)
 * 
 * If either of these macros is not defined at compile time or
 * defined as less than 2, a corresponding error message is
 * thrown by this H-file.
 */
#pragma once
#include <stdint.h>

/**
 * Macro Assignment Checks
 */

// Check MAX_A macro definition
#if !defined(DISCRETE_FILTER_MAX_A) || DISCRETE_FILTER_MAX_A < 2
#error Must define DISCRETE_FILTER_MAX_A as integer >= 2
#endif

// Check MAX_B macro definition
#if !defined(DISCRETE_FILTER_MAX_B) || DISCRETE_FILTER_MAX_B < 2
#error Must define DISCRETE_FILTER_MAX_B as integer >= 2
#endif

/**
 * Class Declaration
 */
class DiscreteFilter {
public:

	// Class Routines
	DiscreteFilter(
		uint8_t A, float* a,
		uint8_t B, float* b);
	DiscreteFilter();
	float update(float xn);
	void reset();

	// Convolution Operation
	friend DiscreteFilter operator*(DiscreteFilter f1, DiscreteFilter f2);

	// Factory Routines
	static DiscreteFilter make_lpf(float f_cutoff, float f_sample);
	static DiscreteFilter make_hpf(float f_cutoff, float f_sample);
	static DiscreteFilter make_int(float f_sample);
	static DiscreteFilter make_dif(float f_sample);

private:
	
	// Array placeholder for {a, b} in default constructor
	static float ab_ph[1];

	// State data
	uint8_t A, B;
	uint8_t frame;
	float a[DISCRETE_FILTER_MAX_A];
	float b[DISCRETE_FILTER_MAX_B];
	float y[DISCRETE_FILTER_MAX_A];
	float x[DISCRETE_FILTER_MAX_B];
};

/**
 * Array Convolution Operation
 */
void conv(float* x1, uint8_t N1, float* x2, uint8_t N2, float* y);