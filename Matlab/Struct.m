classdef Struct < handle
    %STRUCT Class for interpreting byte arrays as C data types
    %   Written by Dan Oates (WPI Class of 2020)
    %   
    %   The Struct class has similar functionality to the Python struct
    %   module. The 'get' and 'set' methods pack and unpack arbitrarily-
    %   typed primitive data into and from its buffer, respectively.
    %   The buffer is automatically reset when switching between 'get'
    %   and 'set', and other methods allow for direct buffer access.
    
    properties (Access = public)
        buffer_;    % Byte buffer
    end
    
    methods
        function obj = Struct(buffer_)
            %obj = STRUCT(buffer_) Construct Struct object
            %   buffer_ = Buffer of bytes [default empty]
            if nargin < 1
                buffer_ = [];
            end
            obj.set_buffer(buffer_);
        end
        function buffer_ = get_buffer(obj)
            %buffer_ = GET_BUFFER(obj) Gets internal buffer
            buffer_ = obj.buffer_;
        end
        function obj = set_buffer(obj, buffer_)
            %obj = SET_BUFFER(obj, buffer_) Sets internal buffer
            obj.buffer_ = uint8(buffer_);
        end
        function obj = reset(obj)
            %obj = RESET(obj) Resets internal buffer to empty
            obj.buffer_ = [];
        end
        function obj = set(obj, val, type_)
            %obj = SET(obj, val, type_) Puts val of type type_ into struct
            sizeof(type_);
            for i = 1:length(val)
                bytes = typecast(cast(val(i), type_), 'uint8');
                obj.buffer_ = [obj.buffer_, bytes];
            end
        end
        function val = get(obj, type_)
            %val = GET(obj, type_) Gets val of type type_ from struct
            n = sizeof(type_);
            val = typecast(obj.buffer_(1:n), type_);
            obj.buffer_ = obj.buffer_(n+1:end);
        end
    end
end

