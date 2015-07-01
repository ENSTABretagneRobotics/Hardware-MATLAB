% Only channel 11 can be used for now...
function [result, value] = GetValueFromThreadMaestro(pMaestro, channel)

value = 0;
pValue = libpointer('int32Ptr', value);

result = calllib('hardwarex', 'GetValueFromThreadMaestrox', pMaestro, channel, pValue);

value = pValue.value;
