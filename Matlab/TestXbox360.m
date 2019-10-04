%% Xbox 360 Controller Test Script
%   Created by Dan Oates (WPI Class of 2020)

% Init Controller
joy_dz = 0.08;
trig_dz = 0;
xbox = Xbox360(1, joy_dz, trig_dz);

% Print Loop
while 1
    clc
    xbox.disp()
    pause(0.1)
end