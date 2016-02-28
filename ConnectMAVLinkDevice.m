function [result] = ConnectMAVLinkDevice(pMAVLinkDevice, szCfgFilePath)
result = calllib('hardwarex', 'ConnectMAVLinkDevicex', pMAVLinkDevice, szCfgFilePath);
