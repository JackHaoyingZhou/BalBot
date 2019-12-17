classdef ClampLimiter < handle
    %CLAMPLIMITER Class for clamp-limiting signals
    %   Author: Dan Oates (WPI Class of 2020)
    
    properties (Access = private)
        x_min;  % Minimum value
        x_max;  % Maximum value
    end
    
    methods
        function obj = ClampLimiter(varargin)
            %CLAMPLIMITER Construct an instance of this class
            %   obj = CLAMPLIMITER(x_min, x_max) will limit inputs x to
            %       range [x_min, x_max]
            %   obj = CLAMPLIMITER(x_max) will limit inputs x to
            %       range [-x_max, +x_max]
            if nargin == 2
                obj.x_min = varargin{1};
                obj.x_max = varargin{2};
            elseif nargin == 1
                obj.x_min = -varargin{1};
                obj.x_max = +varargin{1};
            else
                error('Invalid number of arguments.')
            end
        end
        
        function set_min(obj, x_min)
            %SET_MIN(obj, x_min) Sets minimum output to x_min
            obj.x_min = x_min;
        end
        
        function set_max(obj, x_max)
            %SET_MAX(obj, x_max) Sets maximum output to x_max
            obj.x_max = x_max;
        end
        
        function x = update(obj, x)
            %x = UPDATE(obj, x) Returns x clamped to range [x_min, x_max]
            %   Detailed explanation goes here
            x = clamp_limit(x, obj.x_min, obj.x_max);
        end
    end
end