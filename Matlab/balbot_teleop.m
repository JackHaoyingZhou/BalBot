function balbot_teleop(name, ctrl, vel_max, yaw_max)
%BALBOT_TELEOP Runs bluetooth teleoperation of self-balancing robot.
%   name = Bluetooth device name (ex. 'ES3011_BOT01')
%   ctrl = Controller type ('Xbox360' or 'Nintendo64')
%   vel_max = Max linear velocity command [m/s]
%   yaw_max = Max yaw velocity command [rad/s]

% Default arguments
if nargin < 4
    yaw_max = 1.6;
end
if nargin < 3
    vel_max = 0.8;
end
if nargin < 2
    ctrl = 'Xbox360';
end
if nargin < 1
    name = 'BalBot';
end

% Create game controller interface
switch ctrl
    case 'Xbox360'
        joy_dz = 0.08;  % Joystick deadzone
        trig_dz = 0.01; % Trigger deadzone
        xbox = Xbox360(1, joy_dz, trig_dz);
    case 'Nintendo64'
        joy_dz = 0.04;  % Joystick deadzone
        nin64 = Nintendo64(1, joy_dz);
    otherwise
        error('Invalid controller type')
end

% Connect to robot
clc
fprintf('Balancing Robot Controller\n\n')
fprintf(['Connecting to robot ''' name '''...'])
balbot = BalBot(name, vel_max, yaw_max);
balbot.connect();
pause(2)

% Communication loop
while 1
    
    % Get commands from game controllers
    switch ctrl
        case 'Xbox360'
            vel_cmd = vel_max * xbox.trig();
            yaw_cmd = -yaw_max * xbox.joy_Lx();
        case 'Nintendo64'
            vel_cmd = vel_max * nin64.joy_y();
            yaw_cmd = -yaw_max * nin64.joy_x();
    end
    
    % Send commands to robot and get state
    state = balbot.send_cmds(vel_cmd, yaw_cmd);
    
    % Display state
    clc
    fprintf('Balancing Robot Controller\n\n')
    fprintf('Vel cmd: %+.2f [m/s]\n', vel_cmd)
    fprintf('Lin vel: %+.2f [m/s]\n', state.lin_vel)
    fprintf('Yaw cmd: %+.2f [rad/s]\n', yaw_cmd)
    fprintf('Yaw vel: %+.2f [rad/s]\n', state.yaw_vel)
    fprintf('Voltage L: %+.1f [V]\n', state.volts_L)
    fprintf('Voltage R: %+.1f [V]\n', state.volts_R)
    
    % Exit conditions
    switch ctrl
        case 'Xbox360'
            exit = xbox.btn_B();
        case 'Nintendo64'
            exit = nin64.btn_B();
    end
    if exit
        fprintf('\nProgram terminated by user.\n')
        break
    end
end

% Stop and disconnect from robot
balbot.send_cmds(0, 0);
balbot.disconnect();

end