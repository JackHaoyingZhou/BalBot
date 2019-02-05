%% BalBot Communication and Logging
% Created by Dan Oates (WPI Class of 2020)

%% Setup

% Constants
vel_cmd_max = 0.5;
yaw_cmd_max = 3.0;

% Setup Xbox controller
xbox = XboxController(1, 0.015);

% Create log vectors
log_size = 5000;
t = zeros(log_size, 1);
vel_cmd = zeros(log_size, 1);
yaw_cmd = zeros(log_size, 1);
lin_vel = zeros(log_size, 1);
yaw_vel = zeros(log_size, 1);
volts_L = zeros(log_size, 1);
volts_R = zeros(log_size, 1);

%% Communication loop

% Initialize loop counting and timing
i = 1;                  % Loop counter
log_timer = Timer();    % Loop timer

while 1
    % Get commands from joystick
    js = xbox.LJS();
    vel_cmd(i) = vel_cmd_max * js(2);
    yaw_cmd(i) = -yaw_cmd_max * js(1);
    
    % Communicate with robot
    comms.write_float(vel_cmd(i));
    comms.write_float(yaw_cmd(i));
    if comms.wait(16, 1)
        lin_vel(i) = comms.read_float();
        yaw_vel(i) = comms.read_float();
        volts_L(i) = comms.read_float();
        volts_R(i) = comms.read_float();
        t(i) = log_timer.toc();
        
    else
        error('Communication timeout.')
    end
    
    % Display status:
    clc
    disp('BalBot Controller')
    disp(' ')
    disp(['Vel cmd [m/s]: ' num2str(vel_cmd(i))])
    disp(['Lin vel [m/s]: ' num2str(lin_vel(i))])
    disp(['Yaw cmd [rad/s]: ' num2str(yaw_cmd(i))])
    disp(['Yaw vel [rad/s]: ' num2str(yaw_vel(i))])
    disp(['Volts L [V]: ' num2str(volts_L(i))])
    disp(['Volts R [V]: ' num2str(volts_R(i))])
    
    % Exit condition
    if xbox.B()
        disp('Program terminated by user.')
        t = t(1:i);
        vel_cmd = vel_cmd(1:i);
        yaw_cmd = yaw_cmd(1:i);
        lin_vel = lin_vel(1:i);
        yaw_vel = yaw_vel(1:i);
        volts_L = volts_L(1:i);
        volts_R = volts_R(1:i);
        break
    elseif i == log_size
        disp('Program terminated by time limit.')
        break
    end
    
    % Increment loop counter
    i = i + 1;
end
disp(' ')

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