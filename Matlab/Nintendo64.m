classdef Nintendo64 < handle
    %NINTENDO64 Class for interfacing with Nintendo 64 controllers.
    %   Created by Dan Oates (WPI Class of 2020)
    %
    %   This class has methods for checking the status of every button and
    %   joystick on a connected Nintendo 64 controller.
    %
    %   Button functions 'btn_' return logicals where 1 indicates pressed.
    %   Joystick functions 'joy_' return a single joystick axis (-1 to 1).
    %   The D-pad 'dpad' function returns an angle in deg CW from up.
    %
    %   The constructor has an optional dead-zone parameter for the
    %   joystick inputs to prevent non-zero readings when untouched.
    
    properties
        joy;    % Joystick object [joystick]
        joy_dz; % Joystick dead zone [0-1]
        id;     % Joystick ID [integer]
    end
    
    methods
        function obj = Nintendo64(id, joy_dz)
            %obj = NIN64(id, joy_dz) Construct new Nintendo 64 controller.
            %   id = Controller ID (default 1) [1-4]
            %   joy_dz = Joystick dead zone (default 0) [0-1]
            if nargin < 2
                joy_dz = 0;
            end
            if nargin < 1
                id = 1;
            end
            obj.id = id;
            obj.joy_dz = joy_dz;
            obj.joy = vrjoystick(id);
        end
        function p = btn_start(obj)
            %p = BTN_START(obj) 'START' button status.
            p = button(obj.joy, 10);
        end
        function p = btn_A(obj)
            %p = BTN_A(obj) 'A' button status.
            p = button(obj.joy, 7);
        end
        function p = btn_B(obj)
            %p = BTN_B(obj) 'B' button status.
            p = button(obj.joy, 9);
        end
        function p = btn_CU(obj)
            %p = BTN_CU(obj) 'C' up button status.
            p = button(obj.joy, 1);
        end
        function p = btn_CD(obj)
            %p = BTN_CD(obj) 'C' down button status.
            p = button(obj.joy, 3);
        end
        function p = btn_CL(obj)
            %p = BTN_CL(obj) 'C' left button status.
            p = button(obj.joy, 4);
        end
        function p = btn_CR(obj)
            %p = BTN_CR(obj) 'C' right button status.
            p = button(obj.joy, 2);
        end
        function p = btn_L(obj)
            %p = BTN_L(obj) 'L' button status.
            p = button(obj.joy, 5);
        end
        function p = btn_R(obj)
            %p = BTN_R(obj) 'R' button status.
            p = button(obj.joy, 6);
        end
        function p = btn_Z(obj)
            %p = BTN_Z(obj) 'Z' button status.
            p = button(obj.joy, 8);
        end
        function x = joy_x(obj)
            %x = JOY_X(obj) Joystick x-axis (+right) in range [-1,1].
            x = axis(obj.joy, 1);
            if abs(x) < obj.joy_dz
                x = 0;
            end
        end
        function y = joy_y(obj)
            %y = JOY_Y(obj) Joystick y-axis (+up) in range [-1,1].
            y = -axis(obj.joy, 2);
            if abs(y) < obj.joy_dz
                y = 0;
            end
        end
        function d = dpad(obj)
            %d = DPAD(obj) D-pad angle (deg CW from +y, -1 = no input).
            d = pov(obj.joy, 1);
        end
        function disp(obj)
            %DISP(obj) Displays controller state on command line.
            disp(['Nintendo 64 Controller ' int2str(obj.id)])
            disp(' ')
            disp('Center Button:')
            disp(['START: ' int2str(obj.btn_start())])
            disp(' ')
            disp('Buttons:')
            disp(['A:  ' int2str(obj.btn_A())])
            disp(['B:  ' int2str(obj.btn_B())])
            disp(['CU: ' int2str(obj.btn_CU())])
            disp(['CD: ' int2str(obj.btn_CD())])
            disp(['CL: ' int2str(obj.btn_CL())])
            disp(['CR: ' int2str(obj.btn_CR())])
            disp(['L:  ' int2str(obj.btn_L())])
            disp(['R:  ' int2str(obj.btn_R())])
            disp(['Z:  ' int2str(obj.btn_Z())])
            disp(' ')
            disp('Analog:')
            disp(['joy-x: ' sprintf('%+.4f', obj.joy_x())])
            disp(['joy-y: ' sprintf('%+.4f', obj.joy_y())])
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