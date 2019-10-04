classdef BalBot < handle
    %BALBOT Bluetooth interface for self-balancing robot.
    %   Created by Dan Oates (WPI Class of 2020)

    properties (Access = private)
        device_name;    % Bluetooth device name [String]
        serial_comms;   % Embedded comms interface [SerialComms]
        vel_cmd_max;    % Max velocity cmd [m/s]
        yaw_cmd_max;    % Max yaw velocity cmd [rad/s]
    end
    
    methods
        function obj = BalBot(device_name, vel_max, yaw_max)
            %BALBOT Construct robot interface.
            %   device_name = Bluetooth name (ex. 'ES3011_BOT01')
            %   vel_max = Max linear velocity command [m/s]
            %   yaw_max = Max yaw velocity command [rad/s]
            obj.device_name = device_name;
            obj.vel_cmd_max = vel_max;
            obj.yaw_cmd_max = yaw_max;
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
        function state = send_cmds(obj, vel, yaw)
            %SEND_CMDS Sends commands and returns state struct.
            %   vel = Linear velocity command [m/s]
            %   yaw = Yaw velocity command [rad/s]
            %   state.lin_vel = Robot linear velocity [m/s]
            %   state.yaw_vel = Robot yaw velocity [rad/s]
            %   state.volts_L = Left motor voltage [V]
            %   state.volts_R = Right motor voltage [V]
            vel = clamp_limit(vel, -obj.vel_cmd_max, obj.vel_cmd_max);
            yaw = clamp_limit(yaw, -obj.yaw_cmd_max, obj.yaw_cmd_max);
            obj.serial_comms.write_float(vel);
            obj.serial_comms.write_float(yaw);
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