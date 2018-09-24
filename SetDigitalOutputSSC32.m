function [result] = SetDigitalOutputSSC32(pSSC32, channel, value)
result = calllib('hardwarex', 'SetDigitalOutputSSC32x', pSSC32, channel, value);
