function [result, nmeadata] = GetLatestDataNMEADevice(pNMEADevice)

pNMEAData = calllib('hardwarex', 'CreateNMEADatax');

result = calllib('hardwarex', 'GetLatestDataNMEADevicex', pNMEADevice, pNMEAData);

nmeadata = pNMEAData.value;

calllib('hardwarex', 'DestroyNMEADatax', pNMEAData);
