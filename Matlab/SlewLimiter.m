classdef SlewLimiter < handle
    %SLEWLIMITER Class for limiting the rate of change of a signal
    %   Created by Dan Oates (WPI Class of 2020)
    properties
        delta_min
        delta_max
        first_frame
        val_prev;
    end
    methods
        function obj = SlewLimiter(rate_min, rate_max, f_sample)
            t_sample = 1 / f_sample;
            obj.delta_min = rate_min * t_sample;
            obj.delta_max = rate_max * t_sample;
            obj.first_frame = 0;
            obj.val_prev = 0;
        end
        function val_slew = update(obj, val)
            if obj.first_frame
                obj.first_frame = 0;
                val_slew = val;
            else
                delta = val - obj.val_prev;
                delta = clamp_limit(delta, obj.delta_min, obj.delta_max);
                val_slew = obj.val_prev + delta;
            end
            obj.val_prev = val_slew;
        end
    end
end

