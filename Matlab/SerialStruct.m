classdef SerialStruct < handle
    %SERIALSTRUCT Class for exchanging standard C data types over serial.
    %   Author: Dan Oates (WPI Class of 2020)
    %   
    %   Supported data types:
    %   - Signed ints ('int8', 'int16', 'int32', 'int64')
    %   - Unsigned ints ('uint8', 'uint16', 'uint32', 'uint64')
    %   - Floating point {'single', 'double'}
    
    properties (Access = private, Constant)
        timeout_str = 'Timed out after %.2f second(s)';
    end
    properties (Access = private)
        serial_     % Serial interface [serial]
        timeout     % Read timeout [s]
        struct_     % Struct object [Struct]
    end
    
    methods (Access = public)
        function obj = SerialStruct(serial_, timeout)
            %obj = SERIALSTRUCT(serial_, timeout) Class constructor
            %   serial_ = serial or Bluetooth object
            %   timeout = Read timeout [s] (default 1.0)
            if nargin < 2
                timeout = 1.0;
            end
            obj.serial_ = serial_;
            obj.timeout = timeout;
            obj.struct_ = Struct();
        end
        function serial_ = get_serial(obj)
            %serial_ = GET_SERIAL(obj) Returns serial port object
            serial_ = obj.serial_;
        end
        function obj = set_timeout(obj, timeout)
            %obj = SET_TIMEOUT(obj, timeout) Sets read timeout [s]
            obj.timeout = timeout;
        end
        function obj = wait(obj, n)
            %obj = WAIT(obj, n) Waits for n incoming bytes
            t_init = tic();
            while obj.serial_.BytesAvailable < n
                if toc(t_init) >= obj.timeout
                    error(obj.timeout_str, obj.timeout)
                end
            end
        end
        function val = read(obj, type_)
            %val = READ(obj, type_) Reads data from serial port
            %   val = Value returned [numeric]
            %   type_ = Data type [char]
            n = sizeof(type_);
            obj.wait(n);
            buffer = fread(obj.serial_, n);
            val = obj.struct_.set_buffer(buffer).get(type_);
        end
        function write(obj, val, type_)
            %WRITE(obj, val, type_) Writes data to serial port
            %   val = Value to write [numeric]
            %   type_ = Data type [char]
            obj.struct_.reset().set(val, type_);
            bytes = obj.struct_.get_buffer();
            fwrite(obj.serial_, bytes);
        end
        function delete(obj)
            %DELETE(obj) Destructor which closes serial port
            fclose(obj.serial_);
        end
    end
end