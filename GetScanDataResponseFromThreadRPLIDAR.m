function [result, distance, angle, bNewScan, Quality] = GetScanDataResponseFromThreadRPLIDAR(pRPLIDAR)

distance = 0;
angle = 0;
bNewScan = 0;
Quality = 0;

pDistance = libpointer('doublePtr', distance);
pAngle = libpointer('doublePtr', angle);
pbNewScan = libpointer('int32Ptr', bNewScan);
pQuality = libpointer('int32Ptr', Quality);

result = calllib('hardwarex', 'GetScanDataResponseFromThreadRPLIDARx', pRPLIDAR, pDistance, pAngle, pbNewScan, Quality);

distance = pDistance.value;
angle = pAngle.value;
bNewScan = pbNewScan.value;
Quality = pQuality.value;
