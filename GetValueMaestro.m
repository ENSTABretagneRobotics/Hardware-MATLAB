function [result, value] = GetValueMaestro(pMaestro, channel)

value = 0;
pValue = libpointer('int32Ptr', value);

result = calllib('hardwarex', 'GetValueMaestrox', pMaestro, channel, pValue);

value = pValue.value;
