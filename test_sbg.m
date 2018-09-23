hardwarex_init;
pSBG = CreateSBG();
% Check and modify the configuration file if needed...
[result] = ConnectSBG(pSBG, 'SBG0.txt')
%pSBG.value

[result, sbgdata] = GetLatestDataSBG(pSBG);
str = sprintf('Yaw = %f, Pitch = %f, Roll = %f\n', sbgdata.Yaw*180.0/pi, sbgdata.Pitch*180.0/pi, sbgdata.Roll*180.0/pi);
disp(str);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If GetLatestDataSBG() takes too much time, use a thread to access data faster...
[result] = StartThreadSBG(pSBG);

key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    [result, sbgdata] = GetLatestDataFromThreadSBG(pSBG);
    str = sprintf('Yaw = %f, Pitch = %f, Roll = %f\n', sbgdata.Yaw*180.0/pi, sbgdata.Pitch*180.0/pi, sbgdata.Roll*180.0/pi);
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(0.1); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadSBG(pSBG);

close(fig);

[result] = DisconnectSBG(pSBG)
DestroySBG(pSBG);
clear pSBG; clear sbgdata; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
