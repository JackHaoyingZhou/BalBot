/**
 * @file SerialC.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "SerialC.h"
#include <Unions.h>

/**
 * @brief Constructor for SerialC.
 * @param serial Hardware serial port (ex. Serial, Serial3)
 */
SerialC::SerialC(HardwareSerial& serial)
{
	this->serial = &serial;
}

/**
 * @brief Initializes serial at given baud rate.
 */
void SerialC::init(uint32_t baud)
{
	serial->begin(baud);
}

/**
 * @brief Returns number of bytes available to read.
 */
uint16_t SerialC::available()
{
	return serial->available();
}

/**
 * @brief Waits until givem number of bytes are available.
 */
void SerialC::wait(uint16_t bytes)
{
	while((uint16_t)serial->available() < bytes);
}

/**
 * @brief Flushes incoming serial buffer.
 */
void SerialC::flush()
{
	const uint16_t size = available();
	for(uint16_t i = 0; i < size; i++)
	{
		serial->read();
	}
}

/**
 * @brief Reads int8 (1 byte) from serial buffer.
 */
int8_t SerialC::read_int8()
{
	union8_t union8;
	read_bytes(union8.bytes, 1);
	return union8.int8;
}

/**
 * @brief Reads int16 (2 bytes) from serial buffer.
 */
int16_t SerialC::read_int16()
{
	union16_t union16;
	read_bytes(union16.bytes, 2);
	return union16.int16;
}

/**
 * @brief Reads int32 (4 bytes) from serial buffer.
 */
int32_t SerialC::read_int32()
{
	union32_t union32;
	read_bytes(union32.bytes, 4);
	return union32.int32;
}

/**
 * @brief Reads uint8 (1 byte) from serial buffer.
 */
uint8_t SerialC::read_uint8()
{
	union8_t union8;
	read_bytes(union8.bytes, 1);
	return union8.uint8;
}

/**
 * @brief Reads uint16 (2 bytes) from serial buffer.
 */
uint16_t SerialC::read_uint16()
{
	union16_t union16;
	read_bytes(union16.bytes, 2);
	return union16.uint16;
}

/**
 * @brief Reads uint32 (4 bytes) from serial buffer.
 */
uint32_t SerialC::read_uint32()
{
	union32_t union32;
	read_bytes(union32.bytes, 4);
	return union32.uint32;
}

/**
 * @brief Reads float (4 bytes) from serial buffer.
 */
float SerialC::read_float()
{
	union32_t union32;
	read_bytes(union32.bytes, 4);
	return union32.floating;
}

/**
 * @brief Writes int8 (1 byte) to serial buffer.
 */
void SerialC::write_int8(int8_t val)
{
	union8_t union8;
	union8.int8 = val;
	write_bytes(union8.bytes, 1);
}

/**
 * @brief Writes int16 (2 bytes) to serial buffer.
 */
void SerialC::write_int16(int16_t val)
{
	union16_t union16;
	union16.int16 = val;
	write_bytes(union16.bytes, 2);
}

/**
 * @brief Writes int32 (4 bytes) to serial buffer.
 */
void SerialC::write_int32(int32_t val)
{
	union32_t union32;
	union32.int32 = val;
	write_bytes(union32.bytes, 4);
}

/**
 * @brief Writes uint8 (1 byte) to serial buffer.
 */
void SerialC::write_uint8(uint8_t val)
{
	union8_t union8;
	union8.uint8 = val;
	write_bytes(union8.bytes, 1);
}

/**
 * @brief Writes uint16 (2 bytes) to serial buffer.
 */
void SerialC::write_uint16(uint16_t val)
{
	union16_t union16;
	union16.uint16 = val;
	write_bytes(union16.bytes, 2);
}

/**
 * @brief Writes uint32 (4 bytes) to serial buffer.
 */
void SerialC::write_uint32(uint32_t val)
{
	union32_t union32;
	union32.uint32 = val;
	write_bytes(union32.bytes, 4);
}

/**
 * @brief Writes float (4 bytes) to serial buffer.
 */
void SerialC::write_float(float val)
{
	union32_t union32;
	union32.floating = val;
	write_bytes(union32.bytes, 4);
}

/**
 * @brief Reads n bytes from serial into buffer b.
 */
void SerialC::read_bytes(uint8_t* bytes, uint8_t n)
{
	for(uint8_t i = 0; i < n; i++)
	{
		bytes[i] = serial->read();
	}
}

/**
 * @brief Writes n bytes from b into serial buffer.
 */
void SerialC::write_bytes(uint8_t* bytes, uint8_t n)
{	
	for(uint8_t i = 0; i < n; i++)
	{
		serial->write(bytes[i]);
	}
}