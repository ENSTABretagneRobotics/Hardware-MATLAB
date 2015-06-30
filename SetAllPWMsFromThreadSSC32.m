function [result] = SetAllPWMsFromThreadSSC32(pSSC32, selectedchannels, pws)

pSelectedChannels_p = libpointer('int32Ptr', selectedchannels);
pPWs_p = libpointer('int32Ptr', pws);

result = calllib('hardwarex', 'SetAllPWMsFromThreadSSC32x', pSSC32, pSelectedChannels_p, pPWs_p);
