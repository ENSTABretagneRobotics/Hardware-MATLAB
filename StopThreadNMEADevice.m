function [result] = StopThreadNMEADevice(pNMEADevice)
result = calllib('hardwarex', 'StopThreadNMEADevicex', pNMEADevice);
