/**
 * @file I2CReading.h
 * @brief Class for managing I2C register reading with Platform I2C devices
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <I2CDevice.h>

/**
 * Class Declaration
 */
template <typename T>
class I2CReading
{
public:
	I2CReading(I2CDevice* i2c, uint8_t reg_addr);
	void update();
	T get();
	operator T();
protected:
	I2CDevice* i2c;
	uint8_t reg_addr;
	T reading;
	bool updated;
};

/**
 * @brief Constructs I2C reading interface
 * @param i2c Pointer to I2C device to get reading from
 * @param reg_addr Register address of reading on device
 * @param T Type of reading [uint8_t, int16_t, etc.]
 */
template<typename T>
I2CReading<T>::I2CReading(I2CDevice* i2c, uint8_t reg_addr)
{
	this->i2c = i2c;
	this->reg_addr = reg_addr;
	this->updated = false;
}

/**
 * @brief Updates reading after call to I2CDevice::get_seq()
 * 
 * This method invokes I2CDevice::get() of the reading type T.
 */
template <typename T>
void I2CReading<T>::update()
{
	i2c->get(reading);
	updated = true;
}

/**
 * @brief Returns value of reading
 * 
 * If update() was called previously, it returns that reading and resets the
 * updated flag to false. Otherwise, it fetches the data from the device.
 */
template <typename T>
T I2CReading<T>::get()
{
	if (updated)
	{
		updated = false;
		return reading;
	}
	else
	{
		return (T)i2c->get_seq(reg_addr, sizeof(T));
	}
}

/**
 * @brief Operator shorthand for get()
 */
template <typename T>
I2CReading<T>::operator T()
{
	return get();
}
