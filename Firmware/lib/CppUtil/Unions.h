/**
 * @file Unions.h
 * @brief Collection union data types for byte packing.
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <stdint.h>

// 8-bit union
typedef union
{
	uint8_t bytes[1];
	int8_t int8;
	uint8_t uint8;
}
union8_t;

// 16-bit union
typedef union
{
	uint8_t bytes[2];
	int8_t int8s[2];
	uint8_t uint8s[2];
	int16_t int16;
	uint16_t uint16;
}
union16_t;

// 32-bit union
typedef union
{
	uint8_t bytes[4];
	int8_t int8s[4];
	uint8_t uint8s[4];
	int16_t int16s[2];
	uint16_t uint16s[2];
	int32_t int32;
	uint32_t uint32;
	float floating;
}
union32_t;

// 64-bit union
typedef union
{
	uint8_t bytes[8];
	int8_t int8s[8];
	uint8_t uint8s[8];
	int16_t int16s[4];
	uint16_t uint16s[4];
	int32_t int32s[2];
	uint32_t uint32s[2];
	int64_t int64;
	uint64_t uint64;
}
union64_t;