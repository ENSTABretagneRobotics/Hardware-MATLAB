hardwarex_init;
pNMEADevice = CreateNMEADevice();
[result] = ConnectNMEADevice(pNMEADevice, 'NMEADevice0.txt')
pNMEADevice.value

[result, nmeadata] = GetLatestDataNMEADevice(pNMEADevice);
str = sprintf('(LAT,LON) = (%f,%f)\n', nmeadata.Latitude, nmeadata.Longitude);
disp(str);

% If GetLatestDataNMEADevice() takes too much time, use a thread to access data faster...
[result] = StartThreadNMEADevice(pNMEADevice);

while (true)
    [result, nmeadata] = GetLatestDataFromThreadNMEADevice(pNMEADevice);
    str = sprintf('(LAT,LON) = (%f,%f)\n', nmeadata.Latitude, nmeadata.Longitude);
    disp(str);
    pause(0.1);
end

[result] = StopThreadNMEADevice(pNMEADevice);

[result] = DisconnectNMEADevice(pNMEADevice)
DestroyNMEADevice(pNMEADevice);
clear pNMEADevice; clear nmeadata; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
