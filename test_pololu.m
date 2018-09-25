hardwarex_init;
pPololu = CreatePololu();
% Check and modify the configuration file if needed...
[result] = ConnectPololu(pPololu, 'Pololu0.txt')
%pPololu.value

pause(0.1);
[result] = SetPWMPololu(pPololu, 0, 1350);
pause(0.5);
nbchannels = 24;
selectedchannels = zeros(nbchannels,1);
selectedchannels(1) = 1; selectedchannels(2) = 1; selectedchannels(3) = 1;
pws = zeros(nbchannels,1);
pws(1) = 1000; pws(2) = 2000; pws(3) = 1000;
[result] = SetAllPWMsPololu(pPololu, selectedchannels, pws);
pause(0.1);
[result, value] = GetValuePololu(pPololu, 11);
str = sprintf('value = %d\n', value);
disp(str);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If GetValuePololu(), SetAllPWMsPololu()... take too much time, use a thread to access data faster...
[result] = StartThreadPololu(pPololu);

a = 0;
key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    if (mod(a, 2) == 0)
		pws(1) = 1000; pws(2) = 2000; pws(3) = 1250;
        [result] = SetAllPWMsFromThreadPololu(pPololu, selectedchannels, pws);
    else
		pws(1) = 2000; pws(2) = 1000; pws(3) = 1750;
        [result] = SetAllPWMsFromThreadPololu(pPololu, selectedchannels, pws);
    end
    a = a+1;
    [result, value] = GetValueFromThreadPololu(pPololu, 11);
    str = sprintf('a = %d, value = %d\n', a, value);
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(2); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadPololu(pPololu);

close(fig);

[result] = DisconnectPololu(pPololu)
DestroyPololu(pPololu);
clear pPololu; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
