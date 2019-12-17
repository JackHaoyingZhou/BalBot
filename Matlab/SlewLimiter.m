classdef SlewLimiter < handle
    %SLEWLIMITER Class for limiting the rate of a signal
    %   
    %   The output of a slew limiter follows the input signal with a
    %   limited rate of change. On the first call to the update() method
    %   after construction or reset(), the input signal passses directly
    %   to the output.
    %   
    %   Author: Dan Oates (WPI Class of 2020)
    
    properties (Access = private)
        x_prev  % Previout output [units]
        v_min   % Min rate of change [units/s]
        v_max   % Max rate of change [units/s]
        reset_  % Flag for reset [logical]
        timer   % Timer object [Timer]
    end
    
    methods
        function obj = SlewLimiter(varargin)
            %SLEWLIMITER Construct an instance of this class
            %   obj = SLEWLIMITER(v_min, v_max) will limit rate of inputs
            %       x to range [v_min, v_max]
            %   obj = SLEWLIMITER(v_max) will limit rate of inputs
            %       x to range [-v_max, +v_max]
            if nargin == 2
                obj.v_min = varargin{1};
                obj.v_max = varargin{2};
            elseif nargin == 1
                obj.v_min = -varargin{1};
                obj.v_max = +varargin{1};
            else
                error('Invalid number of arguments.')
            end
            obj.x_prev = 0;
            obj.reset_ = 1;
            obj.timer = Timer();
        end
        
        function set_min(obj, v_min)
            %SET_MIN(obj, v_min) Sets minimum rate to v_min
            obj.v_min = v_min;
        end
        
        function set_max(obj, v_max)
            %SET_MAX(obj, v_max) Sets maximum rate to v_max
            obj.v_max = v_max;
        end
        
        function x = update(obj, x)
            %x = UPDATE(obj, x) Slew-limits x
            if obj.reset_
                obj.reset_ = 0;
                obj.timer.tic();
            else
                delta_t = obj.timer.toc();
                obj.timer.tic();
                delta_x_min = obj.v_min * delta_t;
                delta_x_max = obj.v_max * delta_t;
                delta_x = x - obj.x_prev;
                delta_x = clamp_limit(delta_x, delta_x_min, delta_x_max);
                x = obj.x_prev + delta_x;
            end
            obj.x_prev = x;
        end
        
        function reset(obj)
            %RESET(obj) Resets slew limiter
            obj.reset_ = 1;
        end
    end
end