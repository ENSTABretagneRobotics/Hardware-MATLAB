hardwarex_init;
pRPLIDAR = CreateRPLIDAR();
% Check and modify the configuration file if needed...
[result] = ConnectRPLIDAR(pRPLIDAR, 'RPLIDAR0.txt')
%pRPLIDAR.value

[result, distances, angles, bNewScan] = GetExpressScanDataResponseRPLIDAR(pRPLIDAR);
str = sprintf('Distance at %f deg = %f m\n', angles(1)*180.0/pi, distances(1));
disp(str);

fig = figure('Position',[200 200 400 400],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');
scale = 6;

% If GetLatestDataRPLIDAR() takes too much time, use a thread to access data faster... 
[result] = StartThreadRPLIDAR(pRPLIDAR); 

key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on; axis([-scale,scale,-scale,scale]);
    [result, distances, angles, bNewScan] = GetExpressScanDataResponseFromThreadRPLIDAR(pRPLIDAR);
    plot(distances.*cos(angles), distances.*sin(angles), '.');
    pause(0.1); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadRPLIDAR(pRPLIDAR);

close(fig);

[result] = DisconnectRPLIDAR(pRPLIDAR)
DestroyRPLIDAR(pRPLIDAR);
clear pRPLIDAR; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
