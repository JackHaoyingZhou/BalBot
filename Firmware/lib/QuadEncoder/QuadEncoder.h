#include <Arduino.h>

class QuadEncoder
{
public:
	QuadEncoder(uint8_t pin_A, uint8_t pin_B, float cnts_per_rev);
	void init();
	void interrupt_A();
	void interrupt_B();
	void zero();
	float read();
private:
	uint8_t pin_A, pin_B;
	int32_t counts;
	float rad_per_cnt;
};