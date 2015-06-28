function [result, nmeadata] = GetLatestDataFromThreadNMEADevice(pNMEADevice)

pNMEAData_p = calllib('hardwarex', 'CreateNMEADatax');

result = calllib('hardwarex', 'GetLatestDataFromThreadNMEADevicex', pNMEADevice, pNMEAData_p);

nmeadata = pNMEAData_p.value;

calllib('hardwarex', 'DestroyNMEADatax', pNMEAData_p);
