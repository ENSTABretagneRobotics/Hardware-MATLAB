function [result] = StartThreadNMEADevice(pNMEADevice)
result = calllib('hardwarex', 'StartThreadNMEADevicex', pNMEADevice);
