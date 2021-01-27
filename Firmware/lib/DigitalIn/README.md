# DigitalIn
Class for Arduino and Mbed digital inputs  
Written by Dan Oates (WPI Class of 2020)

### Description
This class implements the Mbed DigitalIn class for Arduino to allow for cross-platform libraries. Additionally, the type PinMode from Mbed is defined in this file. For the Mbed platform, PinMode can be one of:

- PullUp
- PullDown
- PullNone
- OpenDrain

For Arduino, only PullUp and PullNone are supported.

### Dependencies
- [Platform](https://github.com/doates625/Platform.git)

### References
- [Mbed DigitalIn](https://os.mbed.com/docs/mbed-os/v5.14/apis/digitalin.html)