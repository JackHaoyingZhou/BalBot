# SerialStruct
Class for sending and receiving standard C data types over serial  
Written by Dan Oates (WPI Class of 2020)

### Description
This class supports both the Arduino and Mbed platforms. For Mbed, read operations will wait indefinitely until enough data is available. For Arduino, the user should check that sufficient bytes are available before reads by calling:
```
SerialStruct::get_serial()->available();
```
This class requires the macro SERIALSTRUCT_BUFFER_SIZE be defined as an integer >= 8. This defines the maximum size of a data type readable and writable by instances of the class.

### Dependencies
- [Platform](https://github.com/doates625/Platform.git)
- [Struct](https://github.com/doates625/Struct.git)

### References
- [Arduino Serial](https://www.arduino.cc/reference/en/language/functions/communication/serial/)
- [Mbed Serial](https://os.mbed.com/handbook/Serial)