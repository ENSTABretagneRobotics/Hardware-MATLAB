function [result] = DisconnectMAVLinkDevice(pMAVLinkDevice)
result = calllib('hardwarex', 'DisconnectMAVLinkDevicex', pMAVLinkDevice);
