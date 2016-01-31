hardwarex_init;
pMT = CreateMT();
% Check and modify the configuration file if needed...
[result] = ConnectMT(pMT, 'MT0.txt')
%pMT.value

[result, mtdata] = GetLatestDataMT(pMT);
str = sprintf('Yaw = %f, Pitch = %f, Roll = %f\n', mtdata.Yaw*180.0/pi, mtdata.Pitch*180.0/pi, mtdata.Roll*180.0/pi);
disp(str);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If GetLatestDataMT() takes too much time, use a thread to access data faster...
[result] = StartThreadMT(pMT);

key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    [result, mtdata] = GetLatestDataFromThreadMT(pMT);
    str = sprintf('Yaw = %f, Pitch = %f, Roll = %f\n', mtdata.Yaw*180.0/pi, mtdata.Pitch*180.0/pi, mtdata.Roll*180.0/pi);
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(0.1); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadMT(pMT);

close(fig);

[result] = DisconnectMT(pMT)
DestroyMT(pMT);
clear pMT; clear mtdata; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
