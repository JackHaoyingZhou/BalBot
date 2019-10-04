classdef Timer < handle
    %TIMER Class for measuring time between events.
    
    properties (Access = private)
        start_time = 0;
    end
    
    methods
        function obj = Timer()
            %obj = TIMER() Constructs and starts new timer.
            obj.tic();
        end
        function tic(obj)
            %TIC(obj) Starts timer.
            obj.start_time = tic;
        end
        function t = toc(obj)
            %t = TOC(obj) Returns time elapsed since last tic.
            t = toc(obj.start_time);
        end
        function s = has_elapsed(obj, t)
            %s = HAS_ELAPSED(obj, t) Returns 1 if t seconds have elapsed
            %since last tic, otherwise 0.
            s = (obj.toc() >= t);
        end
        function wait_until(obj, t)
            %WAIT_UNTIL(obj, t) Pauses program until t seconds have elapsed
            %since last tic.
            while ~obj.has_elapsed(t)
                continue
            end
        end
    end
end