% Only channel 11 can be used for now...
function [result, value] = GetValueFromThreadPololu(pPololu, channel)

value = 0;
pValue = libpointer('int32Ptr', value);

result = calllib('hardwarex', 'GetValueFromThreadPololux', pPololu, channel, pValue);

value = pValue.value;
