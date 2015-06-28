function [result] = ConnectNMEADevice(pNMEADevice, szCfgFilePath)
result = calllib('hardwarex', 'ConnectNMEADevicex', pNMEADevice, szCfgFilePath);
