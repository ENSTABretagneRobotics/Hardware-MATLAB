hardwarex_init;
pNMEADevice = CreateNMEADevice();
% Check and modify the configuration file if needed...
[result] = ConnectNMEADevice(pNMEADevice, 'NMEADevice0.txt')
%pNMEADevice.value

[result, nmeadata] = GetLatestDataNMEADevice(pNMEADevice);
str = sprintf('(LAT,LON) = (%f,%f)\n', nmeadata.Latitude, nmeadata.Longitude);
disp(str);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If GetLatestDataNMEADevice() takes too much time, use a thread to access data faster...
[result] = StartThreadNMEADevice(pNMEADevice);

key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    [result, nmeadata] = GetLatestDataFromThreadNMEADevice(pNMEADevice);
    if ((abs(nmeadata.Latitude) > 0) && (abs(nmeadata.Longitude) > 0)) % Check if latitude and longitude are not 0, which means invalid.
     str = sprintf('(LAT,LON) = (%f,%f)\n', nmeadata.Latitude, nmeadata.Longitude);
    end
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(0.1); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadNMEADevice(pNMEADevice);

close(fig);

[result] = DisconnectNMEADevice(pNMEADevice)
DestroyNMEADevice(pNMEADevice);
clear pNMEADevice; clear nmeadata; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
