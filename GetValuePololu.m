function [result, value] = GetValuePololu(pPololu, channel)

value = 0;
pValue = libpointer('int32Ptr', value);

result = calllib('hardwarex', 'GetValuePololux', pPololu, channel, pValue);

value = pValue.value;
