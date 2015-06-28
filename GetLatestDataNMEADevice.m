function [result, nmeadata] = GetLatestDataNMEADevice(pNMEADevice)

pNMEAData_p = calllib('hardwarex', 'CreateNMEADatax');

result = calllib('hardwarex', 'GetLatestDataNMEADevicex', pNMEADevice, pNMEAData_p);

nmeadata = pNMEAData_p.value;

calllib('hardwarex', 'DestroyNMEADatax', pNMEAData_p);
