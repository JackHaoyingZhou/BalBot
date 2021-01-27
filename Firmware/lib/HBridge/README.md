# HBridge
Class for H-bridge control for Arduino and Mbed  
Written by Dan Oates (WPI Class of 2020)

### Description
H-bridges are used primarily to bidirectionally drive DC motors. This class controls H-bridges via three control lines:

- pwm: PWM output to control duty cycle
- fwd: Forward enable digital output
- rev: Reverse enable digital output

Braking is done by setting a zero duty cycle and writing both the fwd and rev lines low.

### Dependencies
- [CppUtil](https://github.com/doates625/CppUtil.git)
- [Platform](https://github.com/doates625/Platform.git)
- [DigitalOut](https://github.com/doates625/DigitalOut.git)
- [PwmOut](https://github.com/doates625/PwmOut.git)