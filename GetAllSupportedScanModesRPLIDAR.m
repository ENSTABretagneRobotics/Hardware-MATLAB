function [result, scanmodeids, scanmodeuspersamples, scanmodemaxdistances, scanmodeanstypes, scanmodenames] = GetAllSupportedScanModesRPLIDAR(pRPLIDAR)

scanmodeids = repmat(int32(0), [16 1]);
scanmodeuspersamples = repmat(double(0), [16 1]);
scanmodemaxdistances = repmat(double(0), [16 1]);
scanmodeanstypes = repmat(int32(0), [16 1]);
scanmodenames = repmat('0', [16 64]);

pScanModeIDs = libpointer('int32Ptr', scanmodeids);
pScanModeusPerSamples = libpointer('doublePtr', scanmodeuspersamples);
pScanModeMaxDistances = libpointer('doublePtr', scanmodemaxdistances);
pScanModeAnsTypes = libpointer('int32Ptr', scanmodeanstypes);
pScanModeNames = cellstr(scanmodenames);

[result, rplidar, scanmodeids, scanmodeuspersamples, scanmodemaxdistances, scanmodeanstypes, scanmodenames] = calllib('hardwarex', 'GetAllSupportedScanModesRPLIDARx', pRPLIDAR, pScanModeIDs, pScanModeusPerSamples, pScanModeMaxDistances, pScanModeAnsTypes, pScanModeNames);
