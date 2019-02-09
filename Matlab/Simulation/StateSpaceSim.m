%% BalBot State Space Control Simulator
% Created by Dan Oates (WPI Class of 2020)
BalBotConsts;

%% Control Constants

% Pole Placement
px = 10;

% State Space Matrices
A = zeros(3);
A(1,2) = Tg / Ix;
A(1,3) = Gv / (Gt * Ix);
A(2,1) = 1;
A(3,3) = -Gv / (Gt * m * Rw);
B = zeros(3, 1);
B(1) = -1 / (Gt * Ix);
B(3) = 1 / (Gt * m * Rw);
K1 = -(Gt*Ix^2/Tg)*px^3 -(3*Gt*Ix)*px;
K2 = -Gt*Tg - (3*Gt*Ix)*px^2;
K3 = -Gv - (Gt*Ix*Rw*m/Tg)*px^3;
K = [K1, K2, K3];

%% Simulation Setup

% Time Parameters
t_sim = 0.01;   % Simulation step size [s]
t_max = 10;     % Simulation duration [s]

% Time Vectors
t = (0 : t_sim : t_max).';  % Time vector [s]
n = length(t);              % Simulation length [frames]
vel_act = zeros(n, 1);      % Velocity [m/s]
pitch_act = zeros(n, 1);    % Pitch angle [rad]
pitch_cmd = zeros(n, 1);    % Pitch cmd [rad]
voltage = zeros(n, 1);      % Voltage input [V]

% Velocity Command
vel_cmd = zeros(n, 1);
vel_cmd(t >= 0) = 0.3;
vel_cmd(t >= 4) = -0.3;
vel_cmd(t >= 8) = 0.0;

%% Simulation Loop
x = [0; 0; 0];
for i = 1 : n
    
    % Reference input
    xr = [0; 0; vel_cmd(i)];
    ur = Gv * xr(3);
    
    % Controller simulation
    voltage(i) = ur + K*(xr - x);
    u = voltage(i);
    
    % Dynamic simulation
    x = x + (A*x + B*u)*t_sim;
    vel_act(i) = x(3);
    pitch_act(i) = x(2);
end

%% Plot Results
figure(1)
clf

% Pitch Control
subplot(1, 3, 1)
hold on, grid on
title('Pitch Control')
xlabel('Time [s]')
ylabel('Angle [rad]')
plot(t, pitch_act, 'b-')
plot(t, pitch_cmd, 'k--')
legend('Actual', 'Setpoint')
xlim([min(t), max(t)])

% Velocity Control
subplot(1, 3, 2)
hold on, grid on
title('Velocity Control')
xlabel('Time [s]')
ylabel('Velocity [m/s]')
plot(t, vel_act, 'b-')
plot(t, vel_cmd, 'k--')
legend('Actual', 'Setpoint')
xlim([min(t), max(t)])

% Voltage Input
subplot(1, 3, 3)
hold on, grid on
title('Voltage Input')
xlabel('Time [s]')
ylabel('Voltage [V]')
plot(t, voltage, 'r-')
xlim([min(t), max(t)])