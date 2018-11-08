hardwarex_init;
pSSC32 = CreateSSC32();
% Check and modify the configuration file if needed...
[result] = ConnectSSC32(pSSC32, 'SSC320.txt')
%pSSC32.value

pause(0.1);
[result] = SetPWMSSC32(pSSC32, 0, 1350);
pause(0.5);
nbchannels = 32;
selectedchannels = zeros(nbchannels,1);
selectedchannels(1) = 1; selectedchannels(2) = 1; selectedchannels(3) = 1;
pws = zeros(nbchannels,1);
pws(1) = 1000; pws(2) = 2000; pws(3) = 1000;
[result] = SetAllPWMsSSC32(pSSC32, selectedchannels, pws);
pause(0.1);
[result, value] = GetVoltageSSC32(pSSC32, 0);
str = sprintf('value = %d\n', value);
disp(str);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If SetPWMSSC32(), SetAllPWMsSSC32()... take too much time, use a thread to access data faster...
[result] = StartThreadSSC32(pSSC32);

a = 0;
key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    if (mod(a, 2) == 0)
		pws(1) = 1000; pws(2) = 2000; pws(3) = 1250;
        [result] = SetAllPWMsFromThreadSSC32(pSSC32, selectedchannels, pws);
    else
		pws(1) = 2000; pws(2) = 1000; pws(3) = 1750;
        [result] = SetAllPWMsFromThreadSSC32(pSSC32, selectedchannels, pws);
    end
    a = a+1;
    str = sprintf('a = %d\n', a);
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(2); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadSSC32(pSSC32);

close(fig);

[result] = DisconnectSSC32(pSSC32)
DestroySSC32(pSSC32);
clear pSSC32; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
