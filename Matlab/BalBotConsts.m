%% BalBot Constants Loader
% Created by Dan Oates (WPI Class of 2020)
clear
clc

%% Base Constants
Ix = 0.00314;   % Pitch inertia [kg*m^2]
Iz = 0.00150;   % Yaw inertia [kg*m^2]
m = 0.956;      % Robot mass [kg]
g = 9.81;       % Gravity [m/s^2]
dG = 0.033;     % Axis-to-CG distance [m]
dB = 0.171;     % Wheel base [m]
Rw = 0.0336;    % Wheel radius [m]
Rm = 5.4;       % Motor resistnace [Ohm]
Kv = 0.34;      % Motor back-EMF [V/(rad/s)]
Kt = 0.20;      % Motor torque [N*m/A]
Vb = 12.0;      % Battery voltage [V]

%% Derived Constants
Gt = Rm/(2*Kt); % Torque gain [V/(N*m)]
Gv = Kv/Rw;     % velocity gain [V/(m/s)]
Tg = m*g*dG;    % Gravitational torque [N*m]