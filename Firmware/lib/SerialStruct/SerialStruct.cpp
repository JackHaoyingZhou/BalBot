/**
 * @file SerialStruct.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "SerialStruct.h"

/**
 * @brief Constructs new SerialStruct interface.
 * @param serial Serial interface pointer
 */
SerialStruct::SerialStruct(Platform::serial_t* serial) :
	str(this->buffer, Struct::lsb_first)
{
	this->serial = serial;
}

/**
 * @brief Returns pointer to internal serial interface
 */
Platform::serial_t* SerialStruct::get_serial()
{
	return serial;
}

/**
 * @brief Empties incoming serial buffer
 */
void SerialStruct::flush()
{
	#if defined(PLATFORM_ARDUINO)
		while (serial->available())
		{
			serial->read();
		}
	#elif defined(PLATFORM_MBED)
		while (serial->readable())
		{
			serial->getc();
		}
	#endif
}

#if defined(PLATFORM_ARDUINO)

/**
 * @brief Waits for bytes to be available in serial buffer
 * @param num_bytes Number of bytes to wait for
 */
void SerialStruct::wait(uint8_t num_bytes)
{
	while (serial->available() < num_bytes)
	{
		continue;
	}
}

#endif

/**
 * @brief Writes bytes from internal buffer to serial
 * @param num_bytes Number of bytes to write
 * @return Reference to this
 */
SerialStruct& SerialStruct::tx_bytes(uint8_t num_bytes)
{
	for (uint8_t i = 0; i < num_bytes; i++)
	{
		#if defined(PLATFORM_ARDUINO)
			serial->write(buffer[i]);
		#elif defined(PLATFORM_MBED)
			while (!serial->writeable());
			serial->putc(buffer[i]);
		#endif
	}
	return *this;
}

/**
 * @brief Reads bytes from serial to internal buffer
 * @param num_bytes Number of bytes to read
 * @return Reference to this
 */
SerialStruct& SerialStruct::rx_bytes(uint8_t num_bytes)
{
	for (uint8_t i = 0; i < num_bytes; i++)
	{
		#if defined(PLATFORM_ARDUINO)
			buffer[i] = serial->read();
		#elif defined(PLATFORM_MBED)
			while (!serial->readable());
			buffer[i] = serial->getc();
		#endif
	}
	return *this;
}
