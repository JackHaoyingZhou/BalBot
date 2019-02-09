%% BalBot Yaw Velocity Control Simulator
% Created by Dan Oates (WPI Class of 2020)
BalBotConsts;

%% State Space Model
A = -(Gv*dB/2)/(Gt*Iz*Rw/dB);
B = 1/(Gt*Iz*Rw/dB);

%% Control Constants
f_ctrl = 100.0;
t_ctrl = 1 / f_ctrl;
pz = 80;
Kp = (2*Gt*Iz*Rw/dB)*pz - (Gv*dB/2);
Ki = (Gt*Iz*Rw/dB)*pz^2;
Kd = 0;
ff_gain = (Gv*dB/2);
t_del = 0;

%% Time Vectors
f_sim = 5000;
t_sim = 1 / f_sim;
t_max = 5.0;
t = 0 : t_sim : t_max;
n = length(t);
y = zeros(n, 1);
v = zeros(n, 1);
i_del = ceil(t_del * f_sim);

%% Setpoint Command
s = zeros(n, 1);
s(t >= 0) = 1.6;
s(t >= 2) = -1.6;
s(t >= 4) = 0;

%% Simulation Loop
t_update = 0;
pid = Pid(Kp, Ki, Kd, -Vb, Vb, f_ctrl);
for i = 1 : (n-1)
    if t(i) >= t_update
        v_ff = 0; % ff_gain * s(i);
        v(i+i_del) = pid.update(s(i) - y(i), v_ff);
        t_update = t_update + t_ctrl;
    else
        v(i+i_del) = v(i+i_del-1);
    end
    ydot = A*y(i) + B*v(i);
    y(i+1) = y(i) + ydot * t_sim;
end
v = v(1:n);

%% Plot
figure(1)
clf

% Velocity Control
subplot(1, 2, 1)
hold on, grid on
title('Yaw Velocity')
xlabel('Time [s]')
ylabel('Velocity [rad/s]')
plot(t, s, 'k--')
plot(t, y, 'b-')
legend('Setpt', 'Actual')

% Voltage Input
subplot(1, 2, 2)
hold on, grid on
title('Voltage Input')
xlabel('Time [s]')
ylabel('Voltage [V]')
plot(t, v, 'r-')