# I2CReading
Class for managing I2C register reading with Platform I2C devices  
Written by Dan Oates (WPI Class of 2020)

### Description
This class operates as abstraction layer above the I2CDevice class to manage asynchronous I2C reads and accesses. The update() method fetches the register value(s) after a call to I2CDevice::get_seq(). The get() method then returns the value read from the registers. If the update() method was not previously called, then get() fetches the data first, then returns it. This allows for efficient I2C reading across multiple applications. For example, one function may need all 3 axes from a 3-axis gyroscope. This can be done with:
```
I2CDevice i2c(...);
I2CReading<int16_t> gyro_x(&i2c, ...);
I2CReading<int16_t> gyro_y(&i2c, ...);
I2CReading<int16_t> gyro_z(&i2c, ...);
...
i2c.get_seq(start_address, 6);
gyro_x.update();
gyro_y.update();
gyro_z.update();
...
float gx = gyro_x.get() * scale_factor;
float gy = gyro_y.get() * scale_factor;
float gz = gyro_z.get() * scale_factor;
```
This formulation is most efficient as it gets all the registers in one read, which can double the speed in comparison to multiple disjoint reads. However, if another method only needs the z-axis reading, this can be done in only one line of code:
```
float gz = gyro_z.get() * scale_factor;
```
Because the value was not pre-fetched by update(), it is fetched by get(). Thus, the check for whether a reading is current is abstracted away by the class, resulting in code that is denser, more efficient, and less error-prone.

### Dependencies
- [Platform](https://github.com/doates625/Platform.git)
- [I2CDevice](https://github.com/doates625/I2CDevice.git)
- [Struct](https://github.com/doates625/Struct.git)