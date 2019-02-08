%% BalBot Yaw Gain Solver
%   Created by Dan Oates (WPI Class of 2020)

% Solve for Gains
syms Gt Iz Rw dB Gv Kp Ki s p
exp_pole = (Gt*Iz*Rw/dB)*s^2 + (Gv*dB/2 + Kp)*s + Ki;
exp_damp = (Gt*Iz*Rw/dB)*(s + p)^2;
coef_pole = coeffs(exp_pole, s);
coef_damp = coeffs(exp_damp, s);
S = solve(coef_eq == coef_cd, [Kp, Ki]);

% Display Results
clc
disp('Controller gains:')
disp('Kp:')
disp(S.Kp)
disp('Ki:')
disp(S.Ki)