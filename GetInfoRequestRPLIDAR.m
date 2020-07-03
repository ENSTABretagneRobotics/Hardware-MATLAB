function [result, modelID, hardwareVersion, firmwareMajor, firmwareMinor, serialNumber] = GetInfoRequestRPLIDAR(pRPLIDAR)

modelID = 0;
hardwareVersion = 0;
firmwareMajor = 0;
firmwareMinor = 0;
serialNumber = repmat('0', [1 32]);

pModelID = libpointer('int32Ptr', modelID);
pHardwareVersion = libpointer('int32Ptr', hardwareVersion);
pFirmwareMajor = libpointer('int32Ptr', firmwareMajor);
pFirmwareMinor = libpointer('int32Ptr', firmwareMinor);
SerialNumber = libpointer('voidPtr', [int8(serialNumber) 0]);

result = calllib('hardwarex', 'GetInfoRequestRPLIDARx', pRPLIDAR, pModelID, pHardwareVersion, pFirmwareMajor, pFirmwareMinor, SerialNumber);

modelID = pModelID.value;
hardwareVersion = pHardwareVersion.value;
firmwareMajor = pFirmwareMajor.value;
firmwareMinor = pFirmwareMinor.value;
serialNumber = char(SerialNumber.value);
