function [result, distances, angles] = GetLatestDataHokuyo(pHokuyo)

distances = repmat(0, [1 2048]);
angles = repmat(0, [1 2048]);

pDistances_p = libpointer('doublePtr', distances);
pAngles_p = libpointer('doublePtr', angles);

result = calllib('hardwarex', 'GetLatestDataHokuyox', pHokuyo, pDistances_p, pAngles_p);

distances = pDistances_p.value;
angles = pAngles_p.value;
