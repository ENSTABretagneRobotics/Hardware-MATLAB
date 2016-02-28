function [result] = StopThreadMAVLinkDevice(pMAVLinkDevice)
result = calllib('hardwarex', 'StopThreadMAVLinkDevicex', pMAVLinkDevice);
