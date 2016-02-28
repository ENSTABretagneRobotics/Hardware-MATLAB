function [result] = StartThreadMAVLinkDevice(pMAVLinkDevice)
result = calllib('hardwarex', 'StartThreadMAVLinkDevicex', pMAVLinkDevice);
