function [result] = SetAllPWMsPololu(pPololu, selectedchannels, pws)

pSelectedChannels_p = libpointer('int32Ptr', selectedchannels);
pPWs_p = libpointer('int32Ptr', pws);

result = calllib('hardwarex', 'SetAllPWMsPololux', pPololu, pSelectedChannels_p, pPWs_p);
