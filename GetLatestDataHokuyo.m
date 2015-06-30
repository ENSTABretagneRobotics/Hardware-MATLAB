function [result, distances, angles] = GetLatestDataHokuyo(pHokuyo)

distances = repmat(0, [1 2048]);
angles = repmat(0, [1 2048]);

pDistances = libpointer('doublePtr', distances);
pAngles = libpointer('doublePtr', angles);

result = calllib('hardwarex', 'GetLatestDataHokuyox', pHokuyo, pDistances, pAngles);

distances = pDistances.value;
angles = pAngles.value;
