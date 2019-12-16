function balbot_teleop(name, ctrl_type, vel_max, yaw_max)
%BALBOT_TELEOP Runs bluetooth teleoperation of self-balancing robot.
%   name = Bluetooth device name [ex. 'ES3011_BOT01']
%   ctrl_type = Controller type ['Nintendo64', 'Xbox360']
%   vel_max = Max linear velocity command [m/s]
%   yaw_max = Max yaw velocity command [rad/s]

% Default name and controller
if nargin < 1
    name = 'BalBot';
end
if nargin < 2
    ctrl_type = 'Nintendo64';
end

% Default velocity limits
if nargin < 3
    switch name
        case {'BalBot', 'ES3011_BOT01'}
            vel_max = 0.8;
        otherwise
            vel_max = 0.4;
    end
end
if nargin < 4
    switch name
        case {'BalBot', 'ES3011_BOT01'}
            yaw_max = 1.6;
        otherwise
            yaw_max = 0.8;
    end
end

% Create game controller interface
switch ctrl_type
    case 'Nintendo64'
        joy_dz = 0.04;  % Joystick deadzone
        ctrl = Nintendo64(1, joy_dz);
    case 'Xbox360'
        joy_dz = 0.08;  % Joystick deadzone
        trig_dz = 0.01; % Trigger deadzone
        ctrl = Xbox360(1, joy_dz, trig_dz);
    otherwise
        error('Invalid controller type')
end

% Connect to robot
clc
fprintf('Balancing Robot Controller\n')
fprintf(['Connecting to robot ''' name ''' ...\n'])
balbot = BalBot(name, vel_max, yaw_max);
balbot.connect();
pause(2)

% Log vectors
log_n = 10000;
lin_cmd = zeros(log_n, 1);
lin_vel = zeros(log_n, 1);
yaw_cmd = zeros(log_n, 1);
yaw_vel = zeros(log_n, 1);
volts_L = zeros(log_n, 1);
volts_R = zeros(log_n, 1);
t = zeros(log_n, 1);

% Communication loop
timer = Timer();
com_error = 0;
log_i = 1;
while 1
    
    % Get commands from game controller
    switch ctrl_type
        case 'Xbox360'
            lin_cmd(log_i) = vel_max * ctrl.trig();
            yaw_cmd(log_i) = -yaw_max * ctrl.joy_Lx();
        case 'Nintendo64'
            lin_cmd(log_i) = vel_max * ctrl.joy_y();
            yaw_cmd(log_i) = -yaw_max * ctrl.joy_x();
    end
    
    try
        % Send commands to robot and get state
        state = balbot.send_cmds(lin_cmd(log_i), yaw_cmd(log_i));
        
        % Display state
        clc
        fprintf('Balancing Robot Controller\n')
        fprintf('Press B to exit.\n\n')
        fprintf('Vel cmd: %+.2f [m/s]\n', lin_cmd(log_i))
        fprintf('Lin vel: %+.2f [m/s]\n', state.lin_vel)
        fprintf('Yaw cmd: %+.2f [rad/s]\n', yaw_cmd(log_i))
        fprintf('Yaw vel: %+.2f [rad/s]\n', state.yaw_vel)
        fprintf('Voltage L: %+.1f [V]\n', state.volts_L)
        fprintf('Voltage R: %+.1f [V]\n', state.volts_R)

        % Log state
        lin_vel(log_i) = state.lin_vel;
        yaw_vel(log_i) = state.yaw_vel;
        volts_L(log_i) = state.volts_L;
        volts_R(log_i) = state.volts_R;
        t(log_i) = timer.toc();
    catch
        % Communication error
        log_i = log_i - 1;
        com_error = 1;
    end
    
    % Exit conditions
    exit_btn = ctrl.btn_B();
    if exit_btn || com_error
        lin_cmd = lin_cmd(1:log_i);
        lin_vel = lin_vel(1:log_i);
        yaw_cmd = yaw_cmd(1:log_i);
        yaw_vel = yaw_vel(1:log_i);
        volts_L = volts_L(1:log_i);
        volts_R = volts_R(1:log_i);
        t = t(1:log_i);
        if exit_btn
            fprintf('\nProgram terminated by user.\n')
        elseif com_error
            fprintf('\nBluetooth communication error.\n')
        end
        break
    end
    if log_i == log_n
        fprintf('\nProgram terminated automatically.\n')
        break
    end
    
    % Increment log index
    log_i = log_i + 1;
end

% Stop and disconnect from robot
balbot.send_cmds(0, 0);
balbot.disconnect();

% Plot results
figure(1)
clf

% Plot Linear Velocity
subplot(2, 2, 1)
hold on, grid on
title('Linear Velocity')
xlabel('Time [s]')
ylabel('Velocity [m/s]')
plot(t, lin_cmd, 'k--')
plot(t, lin_vel, 'b-')
legend('Setpt', 'Value')

% Plot Yaw Velocity
subplot(2, 2, 2)
hold on, grid on
title('Yaw Velocity')
xlabel('Time [s]')
ylabel('Velocity [rad/s]')
plot(t, yaw_cmd, 'k--')
plot(t, yaw_vel, 'b-')
legend('Setpt', 'Value')

% Plot Voltage-L
subplot(2, 2, 3)
hold on, grid on
title('Voltage-L')
xlabel('Time [s]')
ylabel('Voltage [V]')
plot(t, volts_L, 'r-')

% Plot Voltage-R
subplot(2, 2, 4)
hold on, grid on
title('Voltage-R')
xlabel('Time [s]')
ylabel('Voltage [V]')
plot(t, volts_R, 'r-')

end