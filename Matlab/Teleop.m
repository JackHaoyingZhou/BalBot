%% BalBot Teleoperation Program
%   Created by Dan Oates (WPI Class of 2020)
clear
clc

%% Setup

% BalBot Parameters
name = 'BalBot';    % Bluetooth device name [String]
vel_max = 0.8;      % Max linear velocity [m/s]
yaw_max = 1.6;      % Max yaw velocity [rad/s]

% Create log vectors
log_size = 5000;
t = zeros(log_size, 1);
vel_cmd = zeros(log_size, 1);
yaw_cmd = zeros(log_size, 1);
lin_vel = zeros(log_size, 1);
yaw_vel = zeros(log_size, 1);
volts_L = zeros(log_size, 1);
volts_R = zeros(log_size, 1);

% Init Xbox controller
xbox = Xbox(1, 0.08, 0);

% Start Balbot
balbot = BalBot(name, vel_max, yaw_max);
balbot.connect();

%% Communication loop
i = 1;              % Loop counter
timer = Timer();    % Loop timer
while 1
    
    % Get commands from Xbox controller
    vel_cmd(i) = vel_max * xbox.trig();
    yaw_cmd(i) = -yaw_max * xbox.LJx();
    
    % Communicate with robot
    status = balbot.send_cmds(vel_cmd(i), yaw_cmd(i));
    lin_vel(i) = status.lin_vel;
    yaw_vel(i) = status.yaw_vel;
    volts_L(i) = status.volts_L;
    volts_R(i) = status.volts_R;
    t(i) = timer.toc();
    
    % Display status
    clc
    disp('BalBot Controller')
    disp(' ')
    disp(['Vel cmd [m/s]: ' num2str(vel_cmd(i))])
    disp(['Lin vel [m/s]: ' num2str(lin_vel(i))])
    disp(['Yaw cmd [rad/s]: ' num2str(yaw_cmd(i))])
    disp(['Yaw vel [rad/s]: ' num2str(yaw_vel(i))])
    disp(['Volts L [V]: ' num2str(volts_L(i))])
    disp(['Volts R [V]: ' num2str(volts_R(i))])
    
    % Exit conditions
    if xbox.B()
        disp('Program terminated by user.')
        disp(' ')
        break
    elseif i == log_size
        disp('Program terminated by time limit.')
        disp(' ')
        break
    end
    
    % Increment loop counter
    i = i + 1;
end

% Crop Time Vectors
vel_cmd = vel_cmd(1:i);
yaw_cmd = yaw_cmd(1:i);
lin_vel = lin_vel(1:i);
yaw_vel = yaw_vel(1:i);
volts_L = volts_L(1:i);
volts_R = volts_R(1:i);
t = t(1:i);

% Stop BalBot and disconnect
balbot.send_cmds(0, 0);
balbot.disconnect();

%% Generate plots

% Velocity Control
figure(1)
clf

% Linear Velocity
subplot(1, 2, 1)
hold on, grid on
title('Linear Velocity')
xlabel('Time [s]')
ylabel('Velocity [m/s]')
plot(t, vel_cmd, 'k--')
plot(t, lin_vel, 'b-')
legend('Setpoint', 'Measured')
xlim([min(t), max(t)])

% Yaw Velocity
subplot(1, 2, 2)
hold on, grid on
title('Yaw Velocity')
xlabel('Time [s]')
ylabel('Velocity [rad/s]')
plot(t, yaw_cmd, 'k--')
plot(t, yaw_vel, 'b-')
legend('Setpoint', 'Measured')
xlim([min(t), max(t)])

% Voltage commands
figure(2)
clf, hold on, grid on
title('Voltage Commands')
xlabel('Time [s]')
ylabel('Voltage [V]')
plot(t, volts_L, 'b-')
plot(t, volts_R, 'r-')
legend('Left', 'Right')
xlim([min(t), max(t)])