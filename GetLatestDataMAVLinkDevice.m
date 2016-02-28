function [result, mavlinkdata] = GetLatestDataMAVLinkDevice(pMAVLinkDevice)

pMAVLinkData = calllib('hardwarex', 'CreateMAVLinkDatax');

result = calllib('hardwarex', 'GetLatestDataMAVLinkDevicex', pMAVLinkDevice, pMAVLinkData);

mavlinkdata = pMAVLinkData.value;

calllib('hardwarex', 'DestroyMAVLinkDatax', pMAVLinkData);
