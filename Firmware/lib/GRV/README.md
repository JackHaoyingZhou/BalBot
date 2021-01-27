# GRV
Class for 1-dimensional Gaussian random variable arithmetic  
Written by Dan Oates (WPI Class of 2020)

### Description
This class represents 1D Gaussian random varaibles by their mean 'mean' and variance 'var' in 32-bit floating-point format. Mathematical functions and operators are included which propagate the variance through each calculation via linearization. Note that protections are not included for potentially-singular or invalid operations such as inversion of zero and square root of negative numbers.

### Dependencies
- [CppUtil](https://github.com/doates625/CppUtil.git)