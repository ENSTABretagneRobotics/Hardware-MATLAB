hardwarex_init;
pP33x = CreateP33x();
% Check and modify the configuration file if needed...
[result] = ConnectP33x(pP33x, 'P33x0.txt')
%pP33x.value

[result, pressure] = GetPressureP33x(pP33x);
str = sprintf('Pressure = %f bar\n', pressure);
disp(str);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If GetPressureP33x() takes too much time, use a thread to access data faster...
[result] = StartThreadP33x(pP33x);

key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    [result, pressure] = GetPressureFromThreadP33x(pP33x);
	str = sprintf('Pressure = %f bar\n', pressure);
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(0.1); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadP33x(pP33x);

close(fig);

[result] = DisconnectP33x(pP33x)
DestroyP33x(pP33x);
clear pP33x; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
