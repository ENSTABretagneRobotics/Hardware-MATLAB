function [result, modelID, hardwareVersion, firmwareMajor, firmwareMinor, serialNumber] = GetInfoRequestRPLIDAR(pRPLIDAR)

modelID = 0;
hardwareVersion = 0;
firmwareMajor = 0;
firmwareMinor = 0;
serialNumber = [repmat(int8('0'), [1 32]) int8(0)];

pModelID = libpointer('int32Ptr', modelID);
pHardwareVersion = libpointer('int32Ptr', hardwareVersion);
pFirmwareMajor = libpointer('int32Ptr', firmwareMajor);
pFirmwareMinor = libpointer('int32Ptr', firmwareMinor);
SerialNumber = char(serialNumber);

[result, rplidar, modelID, hardwareVersion, firmwareMajor, firmwareMinor, serialNumber] = calllib('hardwarex', 'GetInfoRequestRPLIDARx', pRPLIDAR, pModelID, pHardwareVersion, pFirmwareMajor, pFirmwareMinor, SerialNumber);
