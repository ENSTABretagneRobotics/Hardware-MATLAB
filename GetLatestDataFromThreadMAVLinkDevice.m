function [result, mavlinkdata] = GetLatestDataFromThreadMAVLinkDevice(pMAVLinkDevice)

pMAVLinkData = calllib('hardwarex', 'CreateMAVLinkDatax');

result = calllib('hardwarex', 'GetLatestDataFromThreadMAVLinkDevicex', pMAVLinkDevice, pMAVLinkData);

mavlinkdata = pMAVLinkData.value;

calllib('hardwarex', 'DestroyMAVLinkDatax', pMAVLinkData);
