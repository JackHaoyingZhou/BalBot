# Timer
Class for Arduino and Mbed event timing  
Written by Dan Oates (WPI Class of 2020)

### Description
This class implements the Mbed Timer class for Arduino toallow for cross-platform libraries and projects. This class uses the Arduino micros() function, and thus requires interrupts to be enabled for accuracy. Because micros() returns a 32-bit integer, the Mbed method Timer::read_high_resolution_us() which returns a 64-bit integer is not implemented by this class.

### Dependencies
- [Platform](https://github.com/doates625/Platform.git)

### References
- [Mbed Timer](https://os.mbed.com/docs/mbed-os/v5.14/mbed-os-api-doxy/_timer_8h_source.html)