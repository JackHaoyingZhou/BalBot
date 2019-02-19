%% State Space Gain Calculator
%   Created by Dan Oates (WPI Class of 2020)
clear
clc

%% Define State-Space Matrices
syms Gt Gv Mx My Tg K1 K2 K3 s p;
A = sym(zeros(3));
A(1,2) = Tg/Mx;
A(1,3) = -Gt*Gv/Mx;
A(2,1) = 1;
A(3,3) = -Gt*Gv/My;
B = sym(zeros(3,1));
B(1,1) = Gt/Mx;
B(3,1) = Gt/My;
K = [K1, K2, K3];
I = eye(3);

%% Solve for Pole-Placed Gains
cp = collect(det(I*s-A+B*K), s);
dp = collect((s+p)^3, s);
coef_cp = coeffs(cp, s);
coef_dp = coeffs(dp, s);
S = solve(coef_cp == coef_dp, [K1, K2, K3]);
K1 = collect(S.K1, p);
K2 = collect(S.K2, p);
K3 = collect(S.K3, p);

%% Display Results
disp('State-Space Gains:')
disp(' ')
disp('K1:')
disp(K1)
disp('K2:')
disp(K2)
disp('K3:')
disp(K3)