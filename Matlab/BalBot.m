classdef BalBot < handle
    %BALBOT Bluetooth interface for self-balancing robot.
    %   Created by Dan Oates (WPI Class of 2020)

    properties (Access = private)
        device_name;    % Bluetooth device name [String]
        serial_comms;   % Embedded comms interface [SerialComms]
        lin_vel_max;    % Max linear velocity cmd [m/s]
        lin_acc_max;    % Max linear acceleration cmd [m/s^2]
        yaw_vel_max;    % Max yaw velocity cmd [rad/s]
        acc_limiter;    % Command acceleration limiter [SlewLimiter]
    end
    
    methods
        function obj = BalBot(...
                bot_name, ...
                lin_vel_max, ...
                lin_acc_max, ...
                yaw_vel_max)
            %BALBOT Construct robot interface.
            %   bot_name = Bluetooth name [ex. 'ES3011_BOT01']
            %   lin_vel_max = Max linear velocity command [m/s]
            %   lin_acc_max = Max linear acceleration command [m/s^2]
            %   yaw_vel_max = Max yaw velocity command [rad/s]
            obj.device_name = bot_name;
            obj.lin_vel_max = lin_vel_max;
            obj.lin_acc_max = lin_acc_max;
            obj.yaw_vel_max = yaw_vel_max;
            obj.acc_limiter = SlewLimiter(-lin_acc_max, lin_acc_max, 10.0); % Bullshit frequency - fix
        end
        function connect(obj)
            %CONNECT Resets bluetooth connection.
            instrreset;
            bt_info = instrhwinfo('bluetooth');
            n = length(bt_info.RemoteNames);
            bt = [];
            for i = 1 : n
                remote_name = bt_info.RemoteNames{i};
                if strcmp(remote_name, obj.device_name)
                    bt = Bluetooth(remote_name, 1);
                end
            end
            if isempty(bt)
                error('Bluetooth not found.')
            end
            obj.serial_comms = SerialComms(bt);
            obj.serial_comms.open();
        end
        function disconnect(obj)
            %DISCONNECT Disconnects from bluetooth.
            obj.serial_comms.close();
        end
        function state = send_cmds(obj, lin_vel, yaw_vel)
            %SEND_CMDS Sends commands and returns state struct.
            %   vel = Linear velocity command [m/s]
            %   yaw = Yaw velocity command [rad/s]
            %   state.lin_vel = Robot linear velocity [m/s]
            %   state.yaw_vel = Robot yaw velocity [rad/s]
            %   state.volts_L = Left motor voltage [V]
            %   state.volts_R = Right motor voltage [V]
            lin_vel = clamp_limit(...
                lin_vel, ...
                -obj.lin_vel_max, ...
                +obj.lin_vel_max);
            lin_vel = obj.acc_limiter.update(lin_vel);
            yaw_vel = clamp_limit(...
                yaw_vel, ...
                -obj.yaw_vel_max, ...
                +obj.yaw_vel_max);
            obj.serial_comms.write_float(lin_vel);
            obj.serial_comms.write_float(yaw_vel);
            state = struct();
            if obj.serial_comms.wait(16, 1)
                state.lin_vel = obj.serial_comms.read_float();
                state.yaw_vel = obj.serial_comms.read_float();
                state.volts_L = obj.serial_comms.read_float();
                state.volts_R = obj.serial_comms.read_float();
            else
                error('Communication timeout.')
            end
        end
    end
end