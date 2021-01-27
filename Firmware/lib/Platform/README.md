# Platform
Embedded system header for Arduino and Mbed projects  
Written by Dan Oates (WPI Class of 2020)

### Description
This file is meant to replace <Arduino.h> and <mbed.h> in libraries which span across both platforms. Instead of putting conditional includes in every file, instead include this file with the following build flag options:  
  
Embedded platform:
- PLATFORM_ARDUINO (Arduino platform)
- PLATFORM_MBED (Mbed platform)

Board operating voltage:
- PLATFORM_5V (5V boards)
- PLATFORM_3V3 (3.3V boards)

If both or neither is included for each option, this header throws an error at compile time. This file also includes functions for global interrupt control, software delays, and a platform-specific pintype_t for use in multi-platform libraries.  
  
Additionally, when the Arduino platform is used, this file undefines some of their bad macro functions such as min and max.