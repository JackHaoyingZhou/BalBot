classdef SerialComms
    %SERIALCOMMS Serial communication interface for embedded systems.
    %   Created by Dan Oates (WPI Class of 2020)
    %
    %   This class supports transmission of stdint and float data types
    %   between Matlab and embedded systems over serial using a serial or
    %   bluetooth Matlab port.
    %
    %   See also: SERIAL, BLUETOOTH
    
    properties (Access = private)
        port    % Serial port interface (bluetooth or serial)
    end
    
    methods
        function obj = SerialComms(port)
            % Constructs comms interface over given port.
            obj.port = port;
        end
        function s = connected(obj)
            % Returns if port is connected or not.
            s = strcmp(obj.port.status, 'open');
        end
        function s = open(obj)
            % Attempts to open serial port and returns status.
            if ~obj.connected()
                fopen(obj.port);
            end
            s = obj.connected();
        end
        function n = available(obj)
            % Returns number of bytes in serial buffer.
            n = obj.port.BytesAvailable;
        end
        function flush(obj)
            % Flushes incoming serial buffer.
            fread(obj.port, obj.available());
        end
        function s = wait(obj, n, timeout)
            % Waits for n bytes to be available within timeout.
            if nargin < 3
                timeout = inf;
            end
            if nargin < 2
                n = 1;
            end
            timer = Timer();
            timer.tic();
            while timer.toc() < timeout
                if obj.available() >= n
                    s = 1;
                    return
                end
            end
            s = 0;
            return
        end
        function write_int8(obj, i)
            % Writes int8 to serial (1 byte).
            fwrite(obj.port, typecast(int8(i), 'uint8'));
        end
        function write_int16(obj, i)
            % Writes int16 to serial (2 bytes).
            fwrite(obj.port, typecast(int16(i), 'uint8'));
        end
        function write_int32(obj, i)
            % Writes int32 to serial (4 bytes).
            fwrite(obj.port, typecast(int32(i), 'uint8'));
        end
        function write_uint8(obj, i)
            % Writes uint8 to serial (1 byte).
            fwrite(obj.port, uint8(i));
        end
        function write_uint16(obj, i)
            % Writes uint16 to serial (2 bytes).
            fwrite(obj.port, typecast(uint16(i), 'uint8'));
        end
        function write_uint32(obj, i)
            % Writes uint32 to serial (4 bytes).
            fwrite(obj.port, typecast(uint32(i), 'uint8'));
        end
        function write_float(obj, f)
            % Writes float to serail buffer (4 bytes).
            fwrite(obj.port, typecast(single(f), 'uint8'));
        end
        function i = read_int8(obj)
            % Reads int8 from serial (1 byte).
            i = typecast(uint8(fread(obj.port, 1)), 'int8');
        end
        function i = read_int16(obj)
            % Reads int16 from serial (2 bytes).
            i = typecast(uint8(fread(obj.port, 2)), 'int16');
        end
        function i = read_int32(obj)
            % Reads int32 from serial (4 bytes).
            i = typecast(uint8(fread(obj.port, 4)), 'int32');
        end
        function u = read_uint8(obj)
            % Reads uint8 from serial (1 byte).
            u = uint8(fread(obj.port, 1));
        end
        function u = read_uint16(obj)
            % Reads uint16 from serial (2 bytes).
            u = typecast(uint8(fread(obj.port, 2)), 'uint16');
        end
        function u = read_uint32(obj)
            % Reads uint32 from serial (4 bytes).
            u = typecast(uint8(fread(obj.port, 4)), 'uint32');
        end
        function f = read_float(obj)
            % Reads float from serial (4 bytes).
            f = double(typecast(uint8(fread(obj.port, 4)), 'single'));
        end
        function close(obj)
            % Closes serial port.
            if obj.connected()
                fclose(obj.port);
            end
        end
        function delete(obj)
            % Closes serail port on deletion.
            obj.close();
        end
    end
end