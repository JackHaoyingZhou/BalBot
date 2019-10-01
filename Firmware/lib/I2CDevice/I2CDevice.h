/**
 * @brief I2CDevice.h
 * @brief Class for abstracting I2C device read-write operations.
 * @author Dan Oates (WPI Class of 2020)
 * 
 * The I2CInterface class is a Wire library wrapper class which
 * simplifies communication code with I2C devices. The class takes
 * a TwoWire pointer, I2C address, and endian enum on construction
 * and has methods for register writing and reading which automatically
 * format and return signed and unsigned integers of up to 64-bits.
 */
#pragma once
#include <Wire.h>
#include <Unions.h>

class I2CDevice
{
public:

	// Endian enum
	typedef enum
	{
		msb_first,	// Big-endian
		lsb_first,	// Little-endian
	}
	endian_t;

	// Constructors
	I2CDevice(TwoWire* wire, uint8_t i2c_addr, endian_t endian);
	I2CDevice();

	// Write Methods
	void write_int8(uint8_t reg_addr, int8_t value);
	void write_int16(uint8_t reg_addr, int16_t value);
	void write_int32(uint8_t reg_addr, int32_t value);
	void write_int64(uint8_t reg_addr, int64_t value);
	void write_uint8(uint8_t reg_addr, uint8_t value);
	void write_uint16(uint8_t reg_addr, uint16_t value);
	void write_uint32(uint8_t reg_addr, uint32_t value);
	void write_uint64(uint8_t reg_addr, uint64_t value);

	// Single read methods
	int8_t read_int8(uint8_t reg_addr);
	int16_t read_int16(uint8_t reg_addr);
	int32_t read_int32(uint8_t reg_addr);
	int64_t read_int64(uint8_t reg_addr);
	uint8_t read_uint8(uint8_t reg_addr);
	uint16_t read_uint16(uint8_t reg_addr);
	uint32_t read_uint32(uint8_t reg_addr);
	uint64_t read_uint64(uint8_t reg_addr);

	// Sequential read methods
	void read_seq(uint8_t reg_addr, uint8_t num_bytes);
	int8_t read_int8();
	int16_t read_int16();
	int32_t read_int32();
	int64_t read_int64();
	uint8_t read_uint8();
	uint16_t read_uint16();
	uint32_t read_uint32();
	uint64_t read_uint64();

private:

	// Device information
	TwoWire* wire;
	uint8_t i2c_addr;
	endian_t endian;

	// Data storage
	union64_t union64;

	// Read-write methods
	void write_bytes(uint8_t reg_addr, uint8_t* buffer, uint8_t num_bytes);
	void read_bytes(uint8_t* buffer, uint8_t num_bytes);
};