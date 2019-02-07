classdef BalBot
    %BALBOT Class for interfacing with self-balancing robot.
    %   Created by Dan Oates (WPI Class of 2020)

    properties (Access = private)
        device_name;    % Bluetooth device name [String]
        serial_comms;   % Embedded comms interface [SerialComms]
        vel_cmd_max;    % Max velocity cmd [m/s]
        yaw_cmd_max;    % Max yaw velocity cmd [rad/s]
    end
    
    methods
        function obj = BalBot(device_name, vel_max, yaw_max)
            %BALBOT Construct an instance of this class.
            %   Detailed explanation goes here
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
        function status = send_cmds(vel, yaw)
            %SEND_CMDS Sends linear and yaw velocity commands and returns
            %robot status struct.
            vel = clamp_limit(vel, -obj.vel_cmd_max, obj.vel_cmd_max);
            yaw = clamp_limit(yaw, -obj.yaw_cmd_max, obj.yaw_cmd_max);
            obj.serial_comms.write_float(vel);
            obj.serial_comms.write_float(yaw);
            status = struct();
            if comms.wait(16, 1)
                status.lin_vel = obj.serial_comms.read_float();
                status.yaw_vel = obj.serial_comms.read_float();
                status.volts_L = obj.serial_comms.read_float();
                status.volts_R = obj.serial_comms.read_float();
            else
                error('Communication timeout.')
            end
        end
    end
end

