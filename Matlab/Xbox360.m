classdef Xbox360 < handle
    %XBOX360 Class for interfacing with Xbox 360 controllers.
    %   Created by Dan Oates (WPI Class of 2020)
    %
    %   This class has methods for checking the status of every button and
    %   joystick on a connected Xbox controller (except the 'Home' button).
    %
    %   Button functions 'btn_' return logicals where 1 indicates pressed.
    %   Joystick functions 'joy_' return a single joystick axis (-1 to 1).
    %   The trigger function 'trig' returns the trigger press (-1 to 1).
    %   The D-pad 'dpad' function returns an angle in deg CW from up.
    %
    %   The constructor has an optional dead-zone parameter for the
    %   joystick and trigger inputs to prevent non-zero readings when
    %   they are untouched.
    
    properties
        joy;        % Joystick object [joystick]
        joy_dz;     % Joystick dead zone [0-1]
        trig_dz;    % Trigger dead zone [0-1]
        id;         % Controller ID [integer]
    end
    
    methods
        function obj = Xbox360(id, joy_dz, trig_dz)
            %obj = Xbox360(id, joy_dz, trig_dz) Construct new Xbox 360
            %controller.
            %   id = Controller ID (default 1) [integer]
            %   joy_dz = Joystick dead zone (default 0) [0-1]
            %   trig_dz = Trigger dead zone (default 0) [0-1]
            if nargin < 3
                trig_dz = 0;
            end
            if nargin < 2
                joy_dz = 0;
            end
            if nargin < 1
                id = 1;
            end
            obj.id = id;
            obj.joy_dz = joy_dz;
            obj.trig_dz = trig_dz;
            obj.joy = vrjoystick(id);
        end
        function p = btn_start(obj)
            %p = BTN_START(obj) 'Start' button status.
            p = button(obj.joy, 8);
        end
        function p = btn_back(obj)
            %p = BTN_BACK(obj) 'Back' button status.
            p = button(obj.joy, 7);
        end
        function p = btn_A(obj)
            %p = BTN_A(obj) 'A' button status.
            p = button(obj.joy, 1);
        end
        function p = btn_B(obj)
            %p = BTN_B(obj) 'B' button status.
            p = button(obj.joy, 2);
        end
        function p = btn_X(obj)
            %p = BTN_X(obj) 'X' button status.
            p = button(obj.joy, 3);
        end
        function p = btn_Y(obj)
            %p = BTN_Y(obj) 'Y' button status.
            p = button(obj.joy, 4);
        end
        function p = btn_LB(obj)
            %p = BTN_LB(obj) 'LB' button status.
            p = button(obj.joy, 5);
        end
        function p = btn_RB(obj)
            %p = BTN_RB(obj) 'RB' button status.
            p = button(obj.joy, 6);
        end
        function p = btn_LS(obj)
            %p = BTN_LS(obj) 'LS' button status.
            p = button(obj.joy, 9);
        end
        function p = btn_RS(obj)
            %p = BTN_RS(obj) 'RS' button status.
            p = button(obj.joy, 10);
        end
        function x = joy_Lx(obj)
            %x = JOY_LX(obj) Left joystick x-axis in range [-1,1].
            x = axis(obj.joy, 1);
            if abs(x) < obj.joy_dz
                x = 0;
            end
        end
        function y = joy_Ly(obj)
            %y = JOY_LY(obj) Left joystick y-axis in range [-1,1].
            y = -axis(obj.joy, 2);
            if abs(y) < obj.joy_dz
                y = 0;
            end
        end
        function x = joy_Rx(obj)
            %x = JOY_RX(obj) Right joystick x-axis in range [-1,1].
            x = axis(obj.joy, 4);
            if abs(x) < obj.joy_dz
                x = 0;
            end
        end
        function y = joy_Ry(obj)
            %y = JOY_RY(obj) Right joystick y-axis in range [-1,1].
            y = -axis(obj.joy, 5);
            if abs(y) < obj.joy_dz
                y = 0;
            end
        end
        function t = trig(obj)
            %t = TRIG(obj) Returns trigger value in range [-1,1].
            t = -axis(obj.joy, 3);
            if abs(t) < obj.trig_dz
                t = 0;
            end
        end
        function d = dpad(obj)
            %d = DPAD(obj) D-pad angle (deg CW from +y, -1 = no input).
            d = pov(obj.joy, 1);
        end
        function disp(obj)
            %DISP(obj) Displays controller state on command line.
            disp(['Xbox Controller ' int2str(obj.id)])
            disp(' ')
            disp('Center Buttons:')
            disp(['Start: ' int2str(obj.btn_start())])
            disp(['Back:  ' int2str(obj.btn_back())])
            disp(' ')
            disp('Buttons:')
            disp(['A:  ' int2str(obj.btn_A())])
            disp(['B:  ' int2str(obj.btn_B())])
            disp(['X:  ' int2str(obj.btn_X())])
            disp(['Y:  ' int2str(obj.btn_Y())])
            disp(['LB: ' int2str(obj.btn_LB())])
            disp(['RB: ' int2str(obj.btn_RB())])
            disp(['LS: ' int2str(obj.btn_LS())])
            disp(['RS: ' int2str(obj.btn_RS())])
            disp(' ')
            disp('Analog:')
            disp(['LJx:  ' sprintf('%+.4f', obj.joy_Lx())])
            disp(['LJy:  ' sprintf('%+.4f', obj.joy_Ly())])
            disp(['RJx:  ' sprintf('%+.4f', obj.joy_Rx())])
            disp(['RJy:  ' sprintf('%+.4f', obj.joy_Ry())])
            disp(['Trig: ' sprintf('%+.4f', obj.trig())])
            disp(' ')
            disp('POV:')
            disp(['D-pad: ' int2str(obj.dpad())])
        end
        function test(obj)
            %TEST(obj) Displays controller state in infinite loop.
            while 1
                clc
                obj.disp()
                pause(0.1)
            end
        end
        function delete(obj)
            %DELETE(obj) Closes joystick interface.
            close(obj.joy);
        end
    end
end