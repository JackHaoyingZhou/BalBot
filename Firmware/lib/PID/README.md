# PID
Class for discrete-time PID controllers  
Written by Dan Oates (WPI Class of 2020)

### Description
This class implements PID control with the following features:

- Output-limiting: Output automatically saturated to range [u_min, u_max]
- Anti-windup: PID terms each constrained separately to prevent integral windup
- Fixed-frequency: Control frequency [f_ctrl] given at construction
- Transient-removal: Derivative term is ignored on the first frame after reset
- Reset method: Resets differentiator and zeros integrator

All calculations are done in 32-bit floating-point.

### Dependencies
- [CppUtil](https://github.com/doates625/CppUtil.git)