%% BalBot State Space Gain Solver
% Created by Dan Oates (WPI Class of 2020)
clear
clc

%% Matrix Definitions
% dx/dt = A*b + B*u
% u = ur + K*(xr - x)
syms s Tg Ix Gv Gt m Rw K1 K2 K3;
A = sym(zeros(3));
A(1,2) = Tg / Ix;
A(1,3) = Gv / (Gt * Ix);
A(2,1) = 1;
A(3,3) = -Gv / (Gt * m * Rw);
B = sym(zeros(3, 1));
B(1) = -1 / (Gt * Ix);
B(3) = 1 / (Gt * m * Rw);
K = [K1, K2, K3];

%% Characteristic Polynomial
syms p;
cp = det(s*eye(3) - A + B*K);
dp = (s + p)^3;
coef_cp = coeffs(cp, s);
coef_dp = coeffs(dp, s);
S = solve(coef_cp == coef_dp, [K1, K2 K3]);

%% Display Results
disp('Controller Gains:')
disp('K1:')
disp(S.K1);
disp('K2:')
disp(S.K2);
disp('K3:')
disp(S.K3);