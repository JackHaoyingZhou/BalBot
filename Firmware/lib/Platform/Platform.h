/**
 * @file Platform.h
 * @brief Embedded system header for Arduino and Mbed projects
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <stdint.h>

/**
 * Platform Macro
 */
#if defined(PLATFORM_ARDUINO) && defined(PLATFORM_MBED)
	#error Cannot define both PLATFORM_ARDUINO and PLATFORM_MBED
#elif defined(PLATFORM_ARDUINO)
	#include <Arduino.h>
	#include <Wire.h>
	#ifdef abs
		#undef abs
	#endif
	#ifdef min
		#undef min
	#endif
	#ifdef max
		#undef max
	#endif
#elif defined(PLATFORM_MBED)
	#include <mbed.h>
#else
	#error Must define PLATFORM_ARDUINO or PLATFORM_MBED
#endif

/**
 * Supply Voltage Macro
 */
#if defined(PLATFORM_5V) && defined(PLATFORM_3V3)
	#error Cannot define both PLATFORM_5V and PLATFORM_3V3
#elif !defined(PLATFORM_5V) && !defined(PLATFORM_3V3)
	#error Must define PLATFORM_5V or PLATFORM_3V3
#endif

/**
 * Namespace Declaration
 */
namespace Platform
{
	// Pin and Serial Type Definitions
	#if defined(PLATFORM_ARDUINO)
		typedef uint8_t pin_t;
		typedef Stream serial_t;
	#elif defined(PLATFORM_MBED)
		typedef PinName pin_t;
		typedef Serial serial_t;
	#endif

	// Operating Voltage
	extern const float vcc;

	// Methods
	void enable_interrupts();
	void disable_interrupts();
	void wait(float s);
	void wait_ms(uint32_t ms);
	void wait_us(uint32_t us);
}
