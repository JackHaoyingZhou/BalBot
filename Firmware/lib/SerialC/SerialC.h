/**
 * @file SerialC.h
 * @brief Class for exchanging standard C data types over serial.
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <Arduino.h>

class SerialC
{
public:
	SerialC(HardwareSerial& serial);
	void init(uint32_t baud);
	uint16_t available();
	void wait(uint16_t bytes = 1);
	void flush();
	int8_t read_int8();
	int16_t read_int16();
	int32_t read_int32();
	uint8_t read_uint8();
	uint16_t read_uint16();
	uint32_t read_uint32();
	float read_float();
	void write_int8(int8_t val);
	void write_int16(int16_t val);
	void write_int32(int32_t val);
	void write_uint8(uint8_t val);
	void write_uint16(uint16_t val);
	void write_uint32(uint32_t val);
	void write_float(float val);
private:
	void read_bytes(uint8_t* bytes, uint8_t n);
	void write_bytes(uint8_t* bytes, uint8_t n);
	HardwareSerial* serial;
};