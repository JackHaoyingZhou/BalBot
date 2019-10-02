function hc06_config(name, pin, baud, port)
    % HC06_CONFIG Configures Hc06 Bluetooth module connected over USB.
    %   HC06_CONFIG(name, pin, baud, port) Completes the following:
    %   - Auto detects device COM port (optional)
    %   - Auto detects device baud rate
    %   - Sets device name to 'name' [string]
    %   - Sets device pin to 'pin' [string]
    %   - Sets device baud rate to 'baud' [int]
    %   - Verifies device response to new baud rate

    % Display
    clc
    disp('Hc06 Configuration Manager')
    disp(' ')
    
    % Check for valid baud rate
    baud_rates = [1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, ...
        230400, 460800, 921600, 1382400];
    baud_ids = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'};
    rate_to_id = containers.Map(baud_rates, baud_ids);
    if ~rate_to_id.isKey(baud)
        error('Invalid baud rate')
    end
    baud_id = rate_to_id(baud);

    
    % Auto-detect COM port
    if nargin < 4
        disp('Auto-detecting COM port...')
        instrreset;
        hwinfo = instrhwinfo('serial');
        port_list = hwinfo.AvailableSerialPorts;
        if ~isempty(port_list)
            port = port_list{1};
            disp(['Found device on ' port])
            disp(' ')
        else
            error('No device detected.')
        end
    else
        disp(['Using device on ' port])
    end
    
    % Auto-detect baud rate
    disp('Auto-detecting baud rate...')
    baud_found = 0;
    serial_port = serial(port);
    fopen(serial_port);
    for i = 1 : length(baud_rates)
        disp(['Testing ' int2str(baud_rates(i)) '...'])
        serial_port.BaudRate = baud_rates(i);
        if at_cmd('AT', 'OK', 1)
            disp('Success!')
            disp(' ')
            baud_found = 1;
            break
        end
    end
    if ~baud_found
        error('Device failed to respond to all baud rates.')
    end

    % Set device name and pin
    disp('Programming device...')
    disp(['Setting name to ''' name '''...'])
    if ~at_cmd(['AT+NAME' name], 'OKsetname')
        error('Failed to set device name.')
    end
    disp(['Setting pin to ''' pin '''...'])
    if ~at_cmd(['AT+PIN' pin], 'OKsetPIN')
        error('Failed to set device pin.')
    end
    disp(['Setting baud to ' num2str(baud) '...'])
    if ~at_cmd(['AT+BAUD' baud_id], ['OK' num2str(baud)])
        error('Failed to set device baud rate.')
    end
    pause(1)
    disp(['Testing new baud rate...'])
    serial_port.BaudRate = baud;
    if ~at_cmd('AT', 'OK', 2)
        error('Device failed to respond at new baud rate.')
    end
    disp(' ')
    
    % Completion message
    disp('Device Configured.')
    disp(' ')
    fclose(serial_port);
    instrreset;
    
    % Sends AT 'cmd' and returns 1 if it receives 'resp' within timeout.
    function ok = at_cmd(cmd, resp, timeout)
        len = length(resp);
        if nargin < 3
            timeout = 1.5;
        end
        fwrite(serial_port, cmd);
        tic;
        while toc < timeout
            if serial_port.BytesAvailable >= len
                str = char(fread(serial_port, len).');
                if strcmp(str, resp)
                    ok = 1;
                else
                    ok = 0;
                end
                return
            end
        end
        ok = 0;
    end
end