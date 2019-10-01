/**
 * @file Timer.h
 * @brief Class and functions for Arduino timing.
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <Arduino.h>

class Timer {
	public:
		Timer();
		void tic();
		float toc();
		bool has_elapsed(float);
		void wait_until(float);
	private:
		uint32_t start_time;
};

float clock_time();
void delay_seconds(float);