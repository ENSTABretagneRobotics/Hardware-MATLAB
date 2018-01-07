hardwarex_init;
pMaestro = CreateMaestro();
% Check and modify the configuration file if needed...
[result] = ConnectMaestro(pMaestro, 'Maestro0.txt')
%pMaestro.value

[result] = SetAllPWMsMaestro(pMaestro, [1 1 1 0 0], [1000 2000 1000 1500 1500]);
[result, value] = GetValueMaestro(pMaestro, 11);
str = sprintf('value = %d\n', value);
disp(str);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If GetValueMaestro(), SetAllPWMsMaestro()... take too much time, use a thread to access data faster...
[result] = StartThreadMaestro(pMaestro);

a = 0;
key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    if (mod(a, 2) == 0)
        [result] = SetAllPWMsFromThreadMaestro(pMaestro, [1 1 1 0 0], [1000 2000 1250 1500 1500]);
    else
        [result] = SetAllPWMsFromThreadMaestro(pMaestro, [1 1 1 0 0], [2000 1000 1750 1500 1500]);
    end
    a = a+1;
    [result, value] = GetValueFromThreadMaestro(pMaestro, 11);
    str = sprintf('a = %d, value = %d\n', a, value);
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(2); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadMaestro(pMaestro);

close(fig);

[result] = DisconnectMaestro(pMaestro)
DestroyMaestro(pMaestro);
clear pMaestro; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
