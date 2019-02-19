%% BalBot Control Simulator
%   Created by Dan Oates (WPI Class of 2020)
clear
clc

%% Simulation Constants

% Timing Constants
f_sim = 10000;  % Simulation frequency [Hz]
t_dur = 10;     % Simulation duration [s]

% BalBot Physical Constants
Ix = 0.00215;   % Pitch inertia [kg*m^2]***
Iz = 0.00110;   % Yaw inertia [kg*m^2]***
m = 0.955;      % Robot mass [kg]
g = 9.81;       % Gravity [m/s^2]
dg = 0.062;     % CG height [m]
dw = 0.085;     % Wheel to CG-Z [m]
dr = 0.034;     % Wheel radius [m]
R = 5.4;        % Motor resistance [Ohm]
Kv = 0.34;      % Back-EMF constant [V/(rad/s)]
Kt = 0.20;      % Torque constant [N*m/A]
Vb = 12.0;      % Battery voltage [V]

% Derived Physical Constants
Mx = Ix*dr/dg;  % Effective X-inertia [kg*m^2]
My = m*dr;      % Effective Y-inertia [kg*m]
Mz = Iz*dr/dw;  % Effective Z-inertia [kg*m^2]
Tg = m*g*dr;    % Gravitational torque [N*m]
Gt = 2*Kt/R;    % Torque-voltage gain [N*m/V]
Gv = Kv/dr;     % Linear back-EMF [V/(m/s)]
Gw = Kv*dw/dr;  % Yaw back-EMF [V/(rad/s)]

%% Controller Constants

% Main Control Constants
f_ctrl = 100;   % Controller frequency [Hz]
p1 = 20.0;      % Pitch control pole [s^-1]
p2 = 10.0;      % Yaw control pole [s^-1]

% Pitch-Velocity Controller
A_ss_p = zeros(3,3);
A_ss_p(1,2) = Tg/Mx;
A_ss_p(1,3) = -Gt*Gv/Mx;
A_ss_p(2,1) = 1;
A_ss_p(3,3) = -Gt*Gv/My;
B_ss_p = zeros(3,1);
B_ss_p(1,1) = Gt/Mx;
B_ss_p(3,1) = Gt/My;
K_ss_p = zeros(1,3);
K_ss_p(1,1) = Mx^2/(Gt*Tg)*p1^3 + 3*Mx/Gt*p1;
K_ss_p(1,2) = 3*Mx/Gt*p1^2 + Tg/Gt;
K_ss_p(1,3) = -Mx*My/(Gt*Tg)*p1^3 - Gv;

% Yaw Velocity Controller
A_ss_y = -Gt*Gw/Mz;
B_ss_y = Gt/Mz;
Kp_y = (2*Mz/Gt)*p2 - Gw;
Ki_y = (Mz/Gt)*p2^2;
Kd_y = 0;
yaw_pi = Pid(Kp_y, Ki_y, Kd_y, -Vb, Vb, f_ctrl);

% Derived Constants
t_sim = 1/f_sim;    % Simulation period [s]
t_ctrl = 1/f_ctrl;  % Control period [s]

%% Simulation Setup

% Log Vectors
t = (0:t_sim:t_dur).';      % Timestamps [s]
pitch_act = zeros(size(t)); % Pitch angle actual [rad]
pitch_set = zeros(size(t)); % Pitch angle setpoint [rad]
vel_act = zeros(size(t));   % Linear velocity actual [m/s]
vel_set = zeros(size(t));   % Linear velocity setpoint [m/s]
yaw_act = zeros(size(t));   % Yaw velocity actual [rad/s]
yaw_set = zeros(size(t));   % Yaw velocity setpoint [rad/s]
v_rght = zeros(size(t));    % Right motor voltage [V]
v_left = zeros(size(t));    % Left motor voltage [V]
v_avg = zeros(size(t));     % Average voltage [V]
v_dif = zeros(size(t));     % Difference voltage [V]

% State Variables
ss_p = [0; 0; 0];   % Pitch-velocity state-space vector
ss_y = 0;           % Yaw velocity state-space vector
t_update = 0;       % Next controller update time [s]

% Linear Velocity Setpoints
vel_set(t >= 1) = 0.8;
vel_set(t >= 5) = -0.8;
vel_set(t >= 9) = 0; 

% Yaw Velocity Setpoints
yaw_set(t >= 0) = 1.6*sin(2*pi*0.1*t);

%% Simulation Loop
for i = 1:length(t)  
    % Controller
    if t(i) >= t_update
        % Pitch-velocity control
        ss_p_ref = [0; 0; vel_set(i)];
        v_avg_ref = Gv*vel_set(i);
        v_avg(i) = v_avg_ref + K_ss_p*(ss_p_ref - ss_p);
        v_avg(i) = clamp_limit(v_avg(i), -Vb, Vb);
        
        % Yaw velocity control
        v_dif_ref = Gw * yaw_set(i);
        v_dif(i) = yaw_pi.update(yaw_set(i) - ss_y, v_dif_ref);
        
        % Motor voltage limiting
        v_rght(i) = clamp_limit(v_avg(i) - v_dif(i), -Vb, Vb);
        v_left(i) = clamp_limit(v_avg(i) + v_dif(i), -Vb, Vb);
        v_avg(i) = 0.5*(v_left(i) + v_rght(i));
        v_dif(i) = 0.5*(v_left(i) - v_rght(i));
        
        % Increment update time
        t_update = t_update + t_ctrl;
    else
        % Voltages remain constant
        v_rght(i) = v_rght(i-1);
        v_left(i) = v_left(i-1);
        v_avg(i) = v_avg(i-1);
        v_dif(i) = v_dif(i-1);
    end
    
    % State-Space Dynamics
    xp_dot = A_ss_p*ss_p + B_ss_p*v_avg(i);
    xy_dot = A_ss_y*ss_y + B_ss_y*v_dif(i);
    ss_p = ss_p + xp_dot*t_sim;
    ss_y = ss_y + xy_dot*t_sim;
    
    % Data Logging
    pitch_act(i) = ss_p(2);
    vel_act(i) = ss_p(3);
    yaw_act(i) = ss_y(1);
end

%% Pitch-Velocity Plots
figure(1), clf

% Linear Velocity Control
subplot(3, 1, 1)
hold on, grid on
title('Linear Velocity Control')
xlabel('Time [s]')
ylabel('Velocity [m/s]')
plot(t, vel_act, 'b-')
plot(t, vel_set, 'k--')
legend('Actual', 'Setpoint')

% Pitch Angle Control
subplot(3, 1, 2)
hold on, grid on
title('Pitch Angle Control')
xlabel('Time [s]')
ylabel('Pitch [rad]')
plot(t, pitch_act, 'b-')
plot(t, pitch_set, 'k--')
legend('Actual', 'Setpoint')

% Average Voltage Input
subplot(3, 1, 3)
hold on, grid on
title('Average Voltage')
xlabel('Time [s]')
ylabel('Voltage [V]')
plot(t, v_avg, 'r-')

%% Yaw Velocity Plots
figure(2), clf

% Yaw Velocity Control
subplot(2, 1, 1)
hold on, grid on
title('Yaw Velocity Control')
xlabel('Time [s]')
ylabel('Velocity [rad/s]')
plot(t, yaw_act, 'b-')
plot(t, yaw_set, 'k--')
legend('Actual', 'Setpoint')

% Difference Voltage Input
subplot(2, 1, 2)
hold on, grid on
title('Difference Voltage')
xlabel('Time [s]')
ylabel('Voltage [V]')
plot(t, v_dif, 'r-')