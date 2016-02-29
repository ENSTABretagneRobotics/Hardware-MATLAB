hardwarex_init;
pMAVLinkDevice = CreateMAVLinkDevice();
% Check and modify the configuration file if needed...
[result] = ConnectMAVLinkDevice(pMAVLinkDevice, 'MAVLinkDevice0.txt')
%pMAVLinkDevice.value

[result, mavlinkdata] = GetLatestDataMAVLinkDevice(pMAVLinkDevice);
latitude = mavlinkdata.gps_raw_int.lat/10000000.0;
longitude = mavlinkdata.gps_raw_int.lon/10000000.0;
yaw = mavlinkdata.attitude.yaw*180.0/pi;
pitch = mavlinkdata.attitude.pitch*180.0/pi;
roll = mavlinkdata.attitude.roll*180.0/pi;
vrx = 0;
vry = 0;
str = sprintf('(LAT,LON) = (%f,%f), Yaw = %f, Pitch = %f, Roll = %f, (vrx,vry) = (%f,%f)\n', latitude, longitude, yaw, pitch, roll, vrx, vry);
disp(str);

fig = figure('Position',[200 200 400 100],'NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal'); axis('off');

% If GetLatestDataMAVLinkDevice() takes too much time, use a thread to access data faster...
[result] = StartThreadMAVLinkDevice(pMAVLinkDevice);

key = 0;
while (isempty(key)||(key ~= 27)) % Wait for ESC key (ASCII code 27).
    clf; hold on;
    [result, mavlinkdata] = GetLatestDataFromThreadMAVLinkDevice(pMAVLinkDevice);
	% Since not all the data are valid at all times, update only valid values and keep previous otherwise...
	if (mavlinkdata.gps_raw_int.fix_type >= 2)
		latitude = mavlinkdata.gps_raw_int.lat/10000000.0;
		longitude = mavlinkdata.gps_raw_int.lon/10000000.0;
	end
	if (abs(mavlinkdata.attitude.yaw) > 0) 
		yaw = mavlinkdata.attitude.yaw*180.0/pi;
	end
	if (abs(mavlinkdata.attitude.pitch) > 0) 
		pitch = mavlinkdata.attitude.pitch*180.0/pi;
	end
	if (abs(mavlinkdata.attitude.roll) > 0) 
		roll = mavlinkdata.attitude.roll*180.0/pi;
	end
	if (mavlinkdata.optical_flow.quality >= pMAVLinkDevice.value.quality_threshold)
		if (abs(mavlinkdata.optical_flow.flow_comp_m_y) > pMAVLinkDevice.value.flow_comp_m_threshold) vrx = mavlinkdata.optical_flow.flow_comp_m_y; else vrx = 0; end
		if (abs(mavlinkdata.optical_flow.flow_comp_m_x) > pMAVLinkDevice.value.flow_comp_m_threshold) vry = mavlinkdata.optical_flow.flow_comp_m_x; else vry = 0; end
	end
	str = sprintf('(LAT,LON) = (%f,%f), Yaw = %f, Pitch = %f, Roll = %f, (vrx,vry) = (%f,%f)\n', latitude, longitude, yaw, pitch, roll, vrx, vry);
    uicontrol('Style','text','String',str,'Units','normalized','Position',[0 0 1 1]);
    pause(0.1); key = get(gcf,'CurrentCharacter');
end

[result] = StopThreadMAVLinkDevice(pMAVLinkDevice);

close(fig);

[result] = DisconnectMAVLinkDevice(pMAVLinkDevice)
DestroyMAVLinkDevice(pMAVLinkDevice);
clear pMAVLinkDevice; clear mavlinkdata; % unloadlibrary might fail if all the variables that use types from the library are not removed...
unloadlibrary('hardwarex');
