function [result, scanmodeid] = GetTypicalScanModeRPLIDAR(pRPLIDAR)

scanmodeid = 0;

pScanModeID = libpointer('int32Ptr', scanmodeid);

result = calllib('hardwarex', 'GetTypicalScanModeRPLIDARx', pRPLIDAR, pScanModeID);

scanmodeid = pScanModeID.value;
