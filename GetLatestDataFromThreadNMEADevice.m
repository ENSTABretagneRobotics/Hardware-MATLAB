function [result, nmeadata] = GetLatestDataFromThreadNMEADevice(pNMEADevice)

pNMEAData = calllib('hardwarex', 'CreateNMEADatax');

result = calllib('hardwarex', 'GetLatestDataFromThreadNMEADevicex', pNMEADevice, pNMEAData);

nmeadata = pNMEAData.value;

calllib('hardwarex', 'DestroyNMEADatax', pNMEAData);
