function [result, voltage] = GetVoltageSSC32(pSSC32, channel)

voltage = 0;
pVoltage = libpointer('doublePtr', voltage);

result = calllib('hardwarex', 'GetVoltageSSC32x', pSSC32, channel, pVoltage);

voltage = pVoltage.value;
