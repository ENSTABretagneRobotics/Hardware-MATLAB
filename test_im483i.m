hardwarex_init;
pIM483I = CreateIM483I();
% Check and modify the configuration file if needed...
[result] = ConnectIM483I(pIM483I, 'IM483I0.txt')
%pIM483I.value

pause(0.1);
[result] = SetMaxAngleIM483I(pIM483I, 0, 1350);
pause(0.5);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If SetMaxAngleIM483I() takes too much time, use a thread to access data faster...
[result] = StartThreadIM483I(pIM483I);

a = 0;
key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    if (mod(a, 2) == 0)
        [result] = SetMaxAngleFromThreadIM483I(pIM483I, 0.25);
    else
        [result] = SetMaxAngleFromThreadIM483I(pIM483I, -0.25);
    end
    a = a+1;
    str = sprintf('a = %d\n', a);
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(2); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadIM483I(pIM483I);

close(fig);

[result] = DisconnectIM483I(pIM483I)
DestroyIM483I(pIM483I);
clear pIM483I; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
