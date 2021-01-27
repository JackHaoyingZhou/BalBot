# SlewLimiter
Class for implementing asymmetric slew limiting  
Written by Dan Oates (WPI Class of 2020)

### Description
This class is used for limiting the rate of change of a value with units 'U' with respect to a time unit 'T'. It assumes a constant sample rate provided in the constructor. Rate limits should be given in units of [U/T] and the sample rate should be given in units of [1/T]. For example, if slew limiting a temperature setpoint in units of [degF / minute], the sample rate should be provided in units of [samples / minute].  
  
On the first frame after construction or reset, the input is assigned directly to the output.

### Dependencies
- [CppUtil](https://github.com/doates625/CppUtil.git)
- [ClampLimiter](https://github.com/doates625/ClampLimiter.git)