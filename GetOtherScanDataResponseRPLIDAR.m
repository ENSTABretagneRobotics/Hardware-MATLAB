function [result, distances, angles, bNewScan, nbMeasurements] = GetOtherScanDataResponseRPLIDAR(pRPLIDAR)

distances = repmat(0, [1 8192]);
angles = repmat(0, [1 8192]);
bNewScan = 0;
nbMeasurements = 96;

pDistances = libpointer('doublePtr', distances);
pAngles = libpointer('doublePtr', angles);
pbNewScan = libpointer('int32Ptr', bNewScan);
pNbMeasurements = libpointer('int32Ptr', nbMeasurements);

result = calllib('hardwarex', 'GetOtherScanDataResponseRPLIDARx', pRPLIDAR, pDistances, pAngles, pbNewScan, pNbMeasurements);

distances = pDistances.value;
angles = pAngles.value;
bNewScan = pbNewScan.value;
nbMeasurements = pNbMeasurements.value;
