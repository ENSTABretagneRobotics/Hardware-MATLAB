function [result] = DisconnectNMEADevice(pNMEADevice)
result = calllib('hardwarex', 'DisconnectNMEADevicex', pNMEADevice);
