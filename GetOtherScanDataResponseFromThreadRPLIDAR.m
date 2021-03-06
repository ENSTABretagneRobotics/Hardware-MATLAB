function [result, distances, angles, bNewScan] = GetOtherScanDataResponseFromThreadRPLIDAR(pRPLIDAR)

distances = repmat(0, [1 32]);
angles = repmat(0, [1 32]);
bNewScan = 0;

pDistances = libpointer('doublePtr', distances);
pAngles = libpointer('doublePtr', angles);
pbNewScan = libpointer('int32Ptr', bNewScan);

result = calllib('hardwarex', 'GetOtherScanDataResponseFromThreadRPLIDARx', pRPLIDAR, pDistances, pAngles, pbNewScan);

distances = pDistances.value;
angles = pAngles.value;
bNewScan = pbNewScan.value;
