function [result] = SetPWMFromThreadSSC32(pSSC32, channel, pw)
result = calllib('hardwarex', 'SetPWMFromThreadSSC32x', pSSC32, channel, pw);
