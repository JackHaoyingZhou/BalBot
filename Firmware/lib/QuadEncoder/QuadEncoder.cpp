#include "QuadEncoder.h"
#include <math.h>

QuadEncoder::QuadEncoder(uint8_t pin_A, uint8_t pin_B, float cnts_per_rev)
{
	this->pin_A = pin_A;
	this->pin_B = pin_B;
	this->counts = 0;
	this->rad_per_cnt = 2.0f * M_PI / cnts_per_rev;
}

void QuadEncoder::init()
{
	pinMode(pin_A, INPUT);
	pinMode(pin_B, INPUT);
}

void QuadEncoder::interrupt_A()
{
	uint8_t read_A = digitalRead(pin_A);
	uint8_t read_B = digitalRead(pin_B);
	if(read_A == read_B)
	{
		counts++;
	}
	else
	{
		counts--;
	}
}
void QuadEncoder::interrupt_B()
{
	uint8_t read_A = digitalRead(pin_A);
	uint8_t read_B = digitalRead(pin_B);
	if(read_A == read_B)
	{
		counts--;
	}
	else
	{
		counts++;
	}
}

void QuadEncoder::zero()
{
	// TODO ADD 'NOINTERRUPTS' HERE
	counts = 0;
}

float QuadEncoder::read()
{
	// TODO ADD 'NOINTERRUPTS' HERE
	return counts * rad_per_cnt;
}