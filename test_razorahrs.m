hardwarex_init;
pRazorAHRS = CreateRazorAHRS();
% Check and modify the configuration file if needed...
[result] = ConnectRazorAHRS(pRazorAHRS, 'RazorAHRS0.txt')
%pRazorAHRS.value

[result, razorahrsdata] = GetLatestDataRazorAHRS(pRazorAHRS);
str = sprintf('Yaw = %f, Pitch = %f, Roll = %f\n', razorahrsdata.Yaw*180.0/pi, razorahrsdata.Pitch*180.0/pi, razorahrsdata.Roll*180.0/pi);
disp(str);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If GetLatestDataRazorAHRS() takes too much time, use a thread to access data faster...
[result] = StartThreadRazorAHRS(pRazorAHRS);

key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    [result, razorahrsdata] = GetLatestDataFromThreadRazorAHRS(pRazorAHRS);
    str = sprintf('Yaw = %f, Pitch = %f, Roll = %f\n', razorahrsdata.Yaw*180.0/pi, razorahrsdata.Pitch*180.0/pi, razorahrsdata.Roll*180.0/pi);
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(0.1); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadRazorAHRS(pRazorAHRS);

close(fig);

[result] = DisconnectRazorAHRS(pRazorAHRS)
DestroyRazorAHRS(pRazorAHRS);
clear pRazorAHRS; clear razorahrsdata; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
