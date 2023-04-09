function [result, distances, angles, nbMeasurements] = GetLast360DataFromThreadRPLIDAR(pRPLIDAR)

distances = repmat(0, [1 8192]);
angles = repmat(0, [1 8192]);
nbMeasurements = 0;

pDistances = libpointer('doublePtr', distances);
pAngles = libpointer('doublePtr', angles);
pNbMeasurements = libpointer('int32Ptr', nbMeasurements);

result = calllib('hardwarex', 'GetLast360DataFromThreadRPLIDARx', pRPLIDAR, pDistances, pAngles, pNbMeasurements);

distances = pDistances.value;
angles = pAngles.value;
nbMeasurements = pNbMeasurements.value;
