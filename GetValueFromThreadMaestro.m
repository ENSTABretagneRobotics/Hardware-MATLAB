function [result, distances, angles] = GetValueFromThreadMaestro(pMaestro)

value = 0;
pValue = libpointer('int32Ptr', value);

result = calllib('hardwarex', 'GetValueFromThreadMaestrox', pMaestro, channel, pValue);

value = pValue.value;
