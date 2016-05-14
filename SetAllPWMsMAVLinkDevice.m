function [result] = SetAllPWMsMAVLinkDevice(pMAVLinkDevice, selectedchannels, pws)

pSelectedChannels_p = libpointer('int32Ptr', selectedchannels);
pPWs_p = libpointer('int32Ptr', pws);

result = calllib('hardwarex', 'SetAllPWMsMAVLinkDevicex', pMAVLinkDevice, pSelectedChannels_p, pPWs_p);
