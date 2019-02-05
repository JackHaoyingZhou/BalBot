% Set up Xbox controller
xbox = XboxController(1, 0.015);

% Log vectors
log_size = 1000;
log_t = zeros(log_size, 1);
log_vel_cmd = zeros(log_size, 1);
log_yaw_cmd = zeros(log_size, 1);
log_pitch = zeros(log_size, 1);

% Communication loop
i_log = 1;
log_timer = Timer();
log_timer.tic();
while 1
    % Get commands from joystick
    js = xbox.LJS();
    vel_cmd = 0.05 * js(2);
    yaw_cmd = -0.5 * js(1);
    
    % Communicate with robot
    comms.write_float(vel_cmd);
    comms.write_float(yaw_cmd);
    if comms.wait(4, 1)
        pitch = comms.read_float();
    else
        error('Communication timeout.')
    end
    
    % Display status:
    clc
    disp('BalBot Controller')
    disp(' ')
    disp(['Vel cmd: ' num2str(vel_cmd) ' [m/s]'])
    disp(['Yaw cmd: ' num2str(yaw_cmd) ' [rad/s]'])
    disp(['Pitch: ' num2str(pitch) ' rad'])
    
    % Log status
    log_t(i_log) = log_timer.toc();
    log_vel_cmd(i_log) = vel_cmd;
    log_yaw_cmd(i_log) = yaw_cmd;
    log_pitch(i_log) = pitch;
    i_log = i_log + 1;
    
    % Exit condition
    if xbox.B()
        disp('Program terminated')
        break
    end
end

% Crop log vectors
n_log = i_log - 1;
log_t = log_t(1:n_log);
log_vel_cmd = log_vel_cmd(1:n_log);
log_yaw_cmd = log_yaw_cmd(1:n_log);
log_pitch = log_pitch(1:n_log);

% Generate plots

% Pitch Control
figure(1)
clf
hold on
grid on
title('Pitch Angle')
xlabel('Time [s]')
ylabel('Pitch [rad]')
plot(log_t, log_pitch, 'b-')
xlim([min(log_t), max(log_t)])

% Velocity Control
figure(2)
clf

% Linear Velocity
subplot(1, 2, 1)
hold on, grid on
title('Linear Velocity')
xlabel('Time [s]')
ylabel('Velocity [m/s]')
plot(log_t, log_vel_cmd, 'b--')
legend('Setpoint')
xlim([min(log_t), max(log_t)])

% Yaw Velocity
subplot(1, 2, 2)
hold on, grid on
title('Yaw Velocity')
xlabel('Time [s]')
ylabel('Velocity [rad/s]')
plot(log_t, log_yaw_cmd, 'b--')
legend('Setpoint')
xlim([min(log_t), max(log_t)])