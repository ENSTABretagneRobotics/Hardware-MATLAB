function [result] = SetPWMSSC32(pSSC32, channel, pw)
result = calllib('hardwarex', 'SetPWMSSC32x', pSSC32, channel, pw);
