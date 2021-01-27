/**
 * @file SerialStruct.h
 * @brief Class for sending and receiving standard C data types over serial
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <Platform.h>
#include <Struct.h>

/**
 * Serial IO Buffer Size
 */
#if SERIALSTRUCT_BUFFER_SIZE < 8
	#error Must define SERIALSTRUCT_BUFFER_SIZE >= 8
#endif

/**
 * Class Declaration
 */
class SerialStruct
{
public:

	// Constructor and basics
	SerialStruct(Platform::serial_t* serial);
	Platform::serial_t* get_serial();
	void flush();
#if defined(PLATFORM_ARDUINO)
	void wait(uint8_t num_bytes);
#endif

	// Getters and setters
	template <typename T> SerialStruct& tx(const T& val);
	template <typename T> SerialStruct& rx(T& val);
	template <typename T> SerialStruct& operator<<(const T& val);
	template <typename T> SerialStruct& operator>>(T& val);
	template <typename T> operator T();

protected:

	// Class members
	Platform::serial_t* serial;
	uint8_t buffer[SERIALSTRUCT_BUFFER_SIZE];
	Struct str;

	// Read-write methods
	SerialStruct& tx_bytes(uint8_t num_bytes);
	SerialStruct& rx_bytes(uint8_t num_bytes);
};

/**
 * @brief Writes bytes from val to serial
 * @param val Value to write
 * @return Reference to this
 */
template <typename T>
SerialStruct& SerialStruct::tx(const T& val)
{
	str.reset() << val;
	return tx_bytes(sizeof(T));
}

/**
 * @brief Reads bytes from serial into val
 * @param val Value to read into
 * @return Reference to this
 */
template <typename T>
SerialStruct& SerialStruct::rx(T& val)
{
	rx_bytes(sizeof(T));
	str.reset() >> val;
	return *this;
}

/**
 * @brief Operator shorthand for TX
 * @param val Value to write
 * @return reference to this
 */
template <typename T>
SerialStruct& SerialStruct::operator<<(const T& val)
{
	return tx(val);
}

/**
 * @brief Operator shorthand for RX
 * @param val Value to read into
 * @return Reference to this
 */
template <typename T>
SerialStruct& SerialStruct::operator>>(T& val)
{
	return rx(val);
}

/**
 * @brief Reads and returns T from serial
 * @return Value read from serial
 */
template <typename T>
SerialStruct::operator T()
{
	T val;
	rx(val);
	return val;
}
