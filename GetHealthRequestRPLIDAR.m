function [result, bProtectionStop] = GetHealthRequestRPLIDAR(pRPLIDAR)

bProtectionStop = 0;

pbProtectionStop = libpointer('int32Ptr', bProtectionStop);

result = calllib('hardwarex', 'GetHealthRequestRPLIDARx', pRPLIDAR, pbProtectionStop);

bProtectionStop = pbProtectionStop.value;
