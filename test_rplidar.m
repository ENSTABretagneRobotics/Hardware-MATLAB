hardwarex_init;
pRPLIDAR = CreateRPLIDAR();
% Check and modify the configuration file if needed...
[result] = ConnectRPLIDAR(pRPLIDAR, 'RPLIDAR0.txt')
%pRPLIDAR.value

% If bStartScanModeAtStartup to 0 in RPLIDAR0.txt...
%[result] = ResetRequestRPLIDAR(pRPLIDAR)
%pause(2)
%[result] = GetStartupMessageRPLIDAR(pRPLIDAR)
%[result] = StopRequestRPLIDAR(pRPLIDAR)
%[result, ModelID, HardwareVersion, FirmwareMajor, FirmwareMinor, SerialNumber] = GetInfoRequestRPLIDAR(pRPLIDAR)
% Not all the models support this function...
%[result, typicalscanmodeid] = GetTypicalScanModeRPLIDAR(pRPLIDAR)
%[result, scanmodeids, scanmodeuspersamples, scanmodemaxdistances, scanmodeanstypes, scanmodenames] = GetAllSupportedScanModesRPLIDAR(pRPLIDAR)
%[result] = SetMotorPWMRequestRPLIDAR(pRPLIDAR, 660)
%[result] = StartScanRequestRPLIDAR(pRPLIDAR)
%%[result] = StartExpressScanRequestRPLIDAR(pRPLIDAR)
%%[result] = StartOtherScanRequestRPLIDAR(pRPLIDAR, typicalscanmodeid)
%pause(2)

% ScanMode parameter in RPLIDAR0.txt might need to be changed depending on what is uncommented here...
[result, distance, angle, bNewScan, quality] = GetScanDataResponseRPLIDAR(pRPLIDAR);
str = sprintf('Distance at %f deg = %f m\n', angle*180.0/pi, distance);
%[result, distances, angles, bNewScan] = GetExpressScanDataResponseRPLIDAR(pRPLIDAR);
%str = sprintf('Distance at %f deg = %f m\n', angles(1)*180.0/pi, distances(1));
%[result, distances, angles, bNewScan, nbMeasurements] = GetOtherScanDataResponseRPLIDAR(pRPLIDAR);
%str = sprintf('Distance at %f deg = %f m\n', angles(1)*180.0/pi, distances(1));
disp(str);

fig = figure('Position',[200 200 400 400],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');
scale = 6;

%[result] = StartScanThreadRPLIDAR(pRPLIDAR); 
%[result] = StartExpressScanThreadRPLIDAR(pRPLIDAR); 
%[result] = StartOtherScanThreadRPLIDAR(pRPLIDAR); 

count = 0; alldistances = []; allangles = [];
key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    [result, distances, angles, bNewScan, quality] = GetScanDataResponseRPLIDAR(pRPLIDAR); nbMeasurements = 1; % A2 Standard Scan mode
    %[result, distances, angles, bNewScan, quality] = GetScanDataResponseFromThreadRPLIDAR(pRPLIDAR); nbMeasurements = 1;
    %[result, distances, angles, bNewScan] = GetExpressScanDataResponseRPLIDAR(pRPLIDAR); nbMeasurements = 32; % A2 Legacy Express Scan mode
    %[result, distances, angles, bNewScan] = GetExpressScanDataResponseFromThreadRPLIDAR(pRPLIDAR); nbMeasurements = 32; 
    %[result, distances, angles, bNewScan, nbMeasurements] = GetOtherScanDataResponseRPLIDAR(pRPLIDAR); % S2 Dense Scan mode
    %[result, distances, angles, bNewScan, nbMeasurements] = GetOtherScanDataResponseFromThreadRPLIDAR(pRPLIDAR);
    for i = 1:nbMeasurements 
       alldistances = [alldistances distances(i)]; allangles = [allangles angles(i)];
    end
    %if bNewScan
    if count > 360 % A2 Standard Scan mode
    %if count > 720/32 % A2 Legacy Express Scan mode
    %if count > 360/0.12/40 % S2 Dense Scan mode
       clf; hold on; axis([-scale,scale,-scale,scale]);
       plot(alldistances.*cos(allangles), alldistances.*sin(allangles), '.');
       pause(0.01); key = get(gcf,'CurrentCharacter');
       count = 0; alldistances = []; allangles = []; 
    end    
    count = count+1;
end

%[result] = StopScanThreadRPLIDAR(pRPLIDAR);
%[result] = StopExpressScanThreadRPLIDAR(pRPLIDAR);
%[result] = StopOtherScanThreadRPLIDAR(pRPLIDAR);

close(fig);

[result] = DisconnectRPLIDAR(pRPLIDAR)
DestroyRPLIDAR(pRPLIDAR);
clear pRPLIDAR; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
