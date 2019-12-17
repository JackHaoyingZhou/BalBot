classdef BalBot < handle
    %BALBOT Bluetooth interface for self-balancing robot.
    %   Created by Dan Oates (WPI Class of 2020)

    properties (Access = private)
        device_name;    % Bluetooth device name [String]
        serial;         % Embedded serial interface [SerialStruct]
        lin_vel_lim;    % Linear velocity limiter [ClampLimiter]
        lin_acc_lim;    % Linear acceleration limiter [SlewLimiter]
        yaw_vel_lim;    % Yaw velocity limiter [ClampLimiter]
    end
    
    methods
        function obj = BalBot(...
                bot_name, ...
                lin_vel_max, ...
                lin_acc_max, ...
                yaw_vel_max)
            %BALBOT Construct robot interface
            %   bot_name = Bluetooth name [ex. 'ES3011_BOT01']
            %   lin_vel_max = Max linear velocity command [m/s]
            %   lin_acc_max = Max linear acceleration command [m/s^2]
            %   yaw_vel_max = Max yaw velocity command [rad/s]
            obj.device_name = bot_name;
            obj.lin_vel_lim = ClampLimiter(lin_vel_max);
            obj.lin_acc_lim = SlewLimiter(lin_acc_max);
            obj.yaw_vel_lim = ClampLimiter(yaw_vel_max);
        end
        function connect(obj)
            %CONNECT Resets bluetooth connection
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
            obj.serial = SerialStruct(bt, 1);
            fopen(obj.serial.get_serial());
        end
        function disconnect(obj)
            %DISCONNECT Disconnects from bluetooth
            fclose(obj.serial.get_serial());
        end
        function state = send_cmds(obj, lin_vel_cmd, yaw_vel_cmd)
            %SEND_CMDS Sends commands and returns state struct
            %   Inputs:
            %       lin_vel_cmd = Linear velocity [m/s]
            %       yaw_vel_cmd = Yaw velocity [rad/s]
            %   Outputs:
            %       state.lin_vel_cmd = Limited linear velocity [m/s]
            %       state.yaw_vel_cmd = Limited yaw velocity [rad/s]
            %       state.lin_vel = Robot linear velocity [m/s]
            %       state.yaw_vel = Robot yaw velocity [rad/s]
            %       state.volts_L = Left motor voltage [V]
            %       state.volts_R = Right motor voltage [V]
            
            % Filter input commands
            lin_vel_cmd = obj.lin_vel_lim.update(lin_vel_cmd);
            lin_vel_cmd = obj.lin_acc_lim.update(lin_vel_cmd);
            yaw_vel_cmd = obj.yaw_vel_lim.update(yaw_vel_cmd);
            
            % Send filtered commands
            obj.serial.write(lin_vel_cmd, 'single');
            obj.serial.write(yaw_vel_cmd, 'single');
            
            % Get state from robot
            state = struct();
            state.lin_vel_cmd = lin_vel_cmd;
            state.yaw_vel_cmd = yaw_vel_cmd;
            state.lin_vel = obj.serial.read('single');
            state.yaw_vel = obj.serial.read('single');
            state.volts_L = obj.serial.read('single');
            state.volts_R = obj.serial.read('single');
        end
    end
end