%% BalBot Startup and Connection Script
%   Created by Dan Oates (WPI Class of 2020)

% BalBot Constants
name = 'BalBot';    % Bluetooth device name [String]
vel_max = 0.8;      % Max linear velocity [m/s]
yaw_max = 1.6;      % Max yaw velocity [rad/s]

% Class Construction
if ~exist('balbot', 'var')
    balbot = BalBot(name, vel_max, yaw_max);
end
balbot.connect();