hardwarex_init;
pHokuyo = CreateHokuyo();
% Check and modify the configuration file if needed...
[result] = ConnectHokuyo(pHokuyo, 'Hokuyo0.txt')
%pHokuyo.value

[result, distances, angles] = GetLatestDataHokuyo(pHokuyo);
str = sprintf('Distance on the left = %f m\n', distances(angle2kHokuyo(pHokuyo, pi/2.0)));
disp(str);

fig = figure('Position',[200 200 400 400],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');
scale = 6;

% If GetLatestDataHokuyo() takes too much time, use a thread to access data faster... 
[result] = StartThreadHokuyo(pHokuyo); 

key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on; axis([-scale,scale,-scale,scale]);
    [result, distances, angles] = GetLatestDataFromThreadHokuyo(pHokuyo);
    plot(distances.*cos(angles), distances.*sin(angles), '.');
    pause(0.1); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadHokuyo(pHokuyo);

close(fig);

[result] = DisconnectHokuyo(pHokuyo)
DestroyHokuyo(pHokuyo);
clear pHokuyo; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
