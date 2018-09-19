hardwarex_init;
pRPLIDAR = CreateRPLIDAR();
% Check and modify the configuration file if needed...
[result] = ConnectRPLIDAR(pRPLIDAR, 'RPLIDAR0.txt')
%pRPLIDAR.value

[result, distance, angle, bNewScan, quality] = GetScanDataResponseRPLIDAR(pRPLIDAR);
str = sprintf('Distance at %f deg = %f m\n', angle*180.0/pi, distance);
%[result, distances, angles, bNewScan] = GetExpressScanDataResponseRPLIDAR(pRPLIDAR);
%str = sprintf('Distance at %f deg = %f m\n', angles(1)*180.0/pi, distances(1));
disp(str);

fig = figure('Position',[200 200 400 400],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');
scale = 6;

% If GetLatestDataRPLIDAR() takes too much time, use a thread to access data faster... 
%[result] = StartScanThreadRPLIDAR(pRPLIDAR); 
%[result] = StartExpressScanThreadRPLIDAR(pRPLIDAR); 

count = 0; clf; hold on; axis([-scale,scale,-scale,scale]);
key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    if count > 360
        count = 0; clf; hold on; axis([-scale,scale,-scale,scale]);
    end    
    [result, distance, angle, bNewScan, quality] = GetScanDataResponseRPLIDAR(pRPLIDAR);
    %[result, distance, angle, bNewScan, quality] = GetScanDataResponseFromThreadRPLIDAR(pRPLIDAR);
    plot(distance.*cos(angle), distance.*sin(angle), '.');
    %[result, distances, angles, bNewScan] = GetExpressScanDataResponseRPLIDAR(pRPLIDAR);
    %[result, distances, angles, bNewScan] = GetExpressScanDataResponseFromThreadRPLIDAR(pRPLIDAR);
    %plot(distances.*cos(angles), distances.*sin(angles), '.');
    count = count+1;
    pause(0.001); key = get(gcf,'CurrentCharacter');
end

%[result] = StopScanThreadRPLIDAR(pRPLIDAR);
%[result] = StopExpressScanThreadRPLIDAR(pRPLIDAR);

close(fig);

[result] = DisconnectRPLIDAR(pRPLIDAR)
DestroyRPLIDAR(pRPLIDAR);
clear pRPLIDAR; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
