function [result] = GetAllValuesPololu(pPololu, selectedchannels, ais)

pSelectedChannels_p = libpointer('int32Ptr', selectedchannels);
pAIs_p = libpointer('int32Ptr', ais);

result = calllib('hardwarex', 'GetAllValuesPololux', pPololu, pSelectedChannels_p, pAIs_p);
