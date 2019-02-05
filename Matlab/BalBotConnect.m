% Settings
device_name = 'BalBot';

% Auto-detect Bluetooth port
instrreset;
bt_info = instrhwinfo('bluetooth');
n = length(bt_info.RemoteNames);
bt = [];
for i = 1 : n
    remote_name = bt_info.RemoteNames{i};
    if strcmp(remote_name, device_name)
        bt = Bluetooth(remote_name, 1);
    end
end
if isempty(bt)
    error('BalBot bluetooth not found.')
end

% Setup serial communication
comms = SerialComms(bt);
if ~comms.open()
    error('Failed to open bluetooth port.')
end