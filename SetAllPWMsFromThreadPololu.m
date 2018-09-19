function [result] = SetAllPWMsFromThreadPololu(pPololu, selectedchannels, pws)

pSelectedChannels_p = libpointer('int32Ptr', selectedchannels);
pPWs_p = libpointer('int32Ptr', pws);

result = calllib('hardwarex', 'SetAllPWMsFromThreadPololux', pPololu, pSelectedChannels_p, pPWs_p);
