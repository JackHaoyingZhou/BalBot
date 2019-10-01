/**
 * @file I2CDevice.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "I2CDevice.h"

/**
 * @brief Constructor for I2C device.
 * @param wire Wire I2C interface (Wire, Wire1, Wire2, ...)
 * @param i2c_addr I2C address of device
 * @param endian Little-endian or Big-endian
 */
I2CDevice::I2CDevice(TwoWire* wire, uint8_t i2c_addr, endian_t endian)
{
	this->wire = wire;
	this->i2c_addr = i2c_addr;
	this->endian = endian;
}

/**
 * @brief Empty constructor for I2C device (for declaration only).
 */
I2CDevice::I2CDevice()
{
	this->wire = &Wire;
	this->i2c_addr = 0x00;
	this->endian = lsb_first;
}

/**
 * @brief Writes int8_t to device register.
 * @param reg_addr Register address to write to
 * @param value Value to write
 */
void I2CDevice::write_int8(uint8_t reg_addr, int8_t value)
{
	union64.int8s[0] = value;
	write_bytes(reg_addr, union64.bytes, 1);
}

/**
 * @brief Writes int16_t to device register.
 * @param reg_addr Register address to write to
 * @param value Value to write
 */
void I2CDevice::write_int16(uint8_t reg_addr, int16_t value)
{
	union64.int16s[0] = value;
	write_bytes(reg_addr, union64.bytes, 2);
}

/**
 * @brief Writes int32_t to device register.
 * @param reg_addr Register address to write to
 * @param value Value to write
 */
void I2CDevice::write_int32(uint8_t reg_addr, int32_t value)
{
	union64.int32s[0] = value;
	write_bytes(reg_addr, union64.bytes, 4);
}

/**
 * @brief Writes int64_t to device register.
 * @param reg_addr Register address to write to
 * @param value Value to write
 */
void I2CDevice::write_int64(uint8_t reg_addr, int64_t value)
{
	union64.int64 = value;
	write_bytes(reg_addr, union64.bytes, 8);
}

/**
 * @brief Writes uint8_t to device register.
 * @param reg_addr Register address to write to
 * @param value Value to write
 */
void I2CDevice::write_uint8(uint8_t reg_addr, uint8_t value)
{
	union64.uint8s[0] = value;
	write_bytes(reg_addr, union64.bytes, 1);
}

/**
 * @brief Writes uint16_t to device register.
 * @param reg_addr Register address to write to
 * @param value Value to write
 */
void I2CDevice::write_uint16(uint8_t reg_addr, uint16_t value)
{
	union64.uint16s[0] = value;
	write_bytes(reg_addr, union64.bytes, 2);
}

/**
 * @brief Writes uint32_t to device register.
 * @param reg_addr Register address to write to
 * @param value Value to write
 */
void I2CDevice::write_uint32(uint8_t reg_addr, uint32_t value)
{
	union64.uint32s[0] = value;
	write_bytes(reg_addr, union64.bytes, 4);
}

/**
 * @brief Writes uint64_t to device register.
 * @param reg_addr Register address to write to
 * @param value Value to write
 */
void I2CDevice::write_uint64(uint8_t reg_addr, uint64_t value)
{
	union64.uint64 = value;
	write_bytes(reg_addr, union64.bytes, 8);
}

/**
 * @brief Reads int8_t from given device register.
 * @param reg_addr Register address to read from
 */
int8_t I2CDevice::read_int8(uint8_t reg_addr)
{
	read_seq(reg_addr, 1);
	return read_int8();
}

/**
 * @brief Reads int16_t from given device register.
 * @param reg_addr Register address to read from
 */
int16_t I2CDevice::read_int16(uint8_t reg_addr)
{
	read_seq(reg_addr, 2);
	return read_int16();
}

/**
 * @brief Reads int32_t from given device register.
 * @param reg_addr Register address to read from
 */
int32_t I2CDevice::read_int32(uint8_t reg_addr)
{
	read_seq(reg_addr, 4);
	return read_int32();
}

/**
 * @brief Reads int64_t from given device register.
 * @param reg_addr Register address to read from
 */
int64_t I2CDevice::read_int64(uint8_t reg_addr)
{
	read_seq(reg_addr, 8);
	return read_int64();
}

/**
 * @brief Reads uint8_t from given device register.
 * @param reg_addr Register address to read from
 */
uint8_t I2CDevice::read_uint8(uint8_t reg_addr)
{
	read_seq(reg_addr, 1);
	return read_uint8();
}

/**
 * @brief Reads uint16_t from given device register.
 * @param reg_addr Register address to read from
 */
uint16_t I2CDevice::read_uint16(uint8_t reg_addr)
{
	read_seq(reg_addr, 2);
	return read_uint16();
}

/**
 * @brief Reads uint32_t from given device register.
 * @param reg_addr Register address to read from
 */
uint32_t I2CDevice::read_uint32(uint8_t reg_addr)
{
	read_seq(reg_addr, 4);
	return read_uint32();
}

/**
 * @brief Reads uint64_t from given device register.
 * @param reg_addr Register address to read from
 */
uint64_t I2CDevice::read_uint64(uint8_t reg_addr)
{
	read_seq(reg_addr, 8);
	return read_uint64();
}

/**
 * @brief Initializes sequential register read in I2C device.
 * @param reg_addr Starting register address
 * @param num_bytes Number of bytes to read starting from reg_addr
 */
void I2CDevice::read_seq(uint8_t reg_addr, uint8_t num_bytes)
{
	wire->beginTransmission(i2c_addr);
	wire->write(reg_addr);
	wire->endTransmission(false);
	const uint8_t send_stop = 1;
	wire->requestFrom(i2c_addr, num_bytes, send_stop);
}

/**
 * @brief Reads int8_t from device after call to read_seq.
 */
int8_t I2CDevice::read_int8()
{
	read_bytes(union64.bytes, 1);
	return union64.int8s[0];
}

/**
 * @brief Reads int16_t from device after call to read_seq.
 */
int16_t I2CDevice::read_int16()
{
	read_bytes(union64.bytes, 2);
	return union64.int16s[0];
}

/**
 * @brief Reads int32_t from device after call to read_seq.
 */
int32_t I2CDevice::read_int32()
{
	read_bytes(union64.bytes, 4);
	return union64.int32s[0];
}

/**
 * @brief Reads int64_t from device after call to read_seq.
 */
int64_t I2CDevice::read_int64()
{
	read_bytes(union64.bytes, 8);
	return union64.int64;
}

/**
 * @brief Reads uint8_t from device after call to read_seq.
 */
uint8_t I2CDevice::read_uint8()
{
	read_bytes(union64.bytes, 1);
	return union64.uint8s[0];
}

/**
 * @brief Reads uint16_t from device after call to read_seq.
 */
uint16_t I2CDevice::read_uint16()
{
	read_bytes(union64.bytes, 2);
	return union64.uint16s[0];
}

/**
 * @brief Reads uint32_t from device after call to read_seq.
 */
uint32_t I2CDevice::read_uint32()
{
	read_bytes(union64.bytes, 4);
	return union64.uint32s[0];
}

/**
 * @brief Reads uint64_t from device after call to read_seq.
 */
uint64_t I2CDevice::read_uint64()
{
	read_bytes(union64.bytes, 8);
	return union64.uint64;
}

/**
 * @brief Writes bytes from buffer to device register.
 * @param reg_addr Device register to write to
 * @param buffer Pointer to byte buffer
 * @param num_bytes Length of byte buffer
 */
void I2CDevice::write_bytes(uint8_t reg_addr, uint8_t* buffer, uint8_t num_bytes)
{
	// Begin write to register address
	wire->beginTransmission(i2c_addr);
	wire->write(reg_addr);

	// Check endian order
	if (endian == lsb_first)
	{
		// LSB first - write in ascending order
		for (uint8_t i = 0; i < num_bytes; i++)
		{
			wire->write(buffer[i]);
		}
	}
	else
	{
		// MSB first - write in descending order
		for (uint8_t i = num_bytes - 1; i < 255; i--)
		{
			wire->write(buffer[i]);
		}
	}

	// End write and free the bus
	wire->endTransmission(true);
}

/**
 * @brief Reads bytes into buffer after call to read_seq.
 * @param buffer Pointer to byte buffer
 * @param num_bytes Length of byte buffer
 */
void I2CDevice::read_bytes(uint8_t* buffer, uint8_t num_bytes)
{
	// Check endian order
	if (endian == lsb_first)
	{
		// LSB first - read in ascending order
		for (uint8_t i = 0; i < num_bytes; i++)
		{
			buffer[i] = wire->read();
		}
	}
	else
	{
		// MSB first - read in descending order
		for (uint8_t i = num_bytes - 1; i < 255; i--)
		{
			buffer[i] = wire->read();
		}
	}
}