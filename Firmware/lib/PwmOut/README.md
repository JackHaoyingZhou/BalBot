# PwmOut
Class for Arduino and Mbed PWM outputs  
Written by Dan Oates (WPI Class of 2020)

### Description
This class implements the Mbed PwmOut class for Arduino to allow for cross-platform libraries. This implementation does NOT include the period and pulsewidth methods offered by Mbed as this level of control is not allowed by the standard Arduino library.

### Dependencies
- [CppUtil](https://github.com/doates625/CppUtil.git)
- [Platform](https://github.com/doates625/Platform.git)

### References
- [Mbed PwmOut](https://os.mbed.com/docs/mbed-os/v5.14/apis/pwmout.html)