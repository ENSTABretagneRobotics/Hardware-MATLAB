function [result, value] = GetDigitalInputSSC32(pSSC32, channel)

value = 0;
pValue = libpointer('int32Ptr', value);

result = calllib('hardwarex', 'GetDigitalInputSSC32x', pSSC32, channel, pValue);

value = pValue.value;
