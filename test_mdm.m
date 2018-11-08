hardwarex_init;
pMDM = CreateMDM();
% Check and modify the configuration file if needed...
[result] = ConnectMDM(pMDM, 'MDM0.txt')
%pMDM.value

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
	buf = zeros(4)
    [result, nbbytes] = RecvDataMDM(pMDM, buf, 4);
	str = sprintf('%D\n', buf(1));
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(1); key = get(gcf,'CurrentCharacter');
end

close(fig);

[result] = DisconnectMDM(pMDM)
DestroyMDM(pMDM);
clear pMDM; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
