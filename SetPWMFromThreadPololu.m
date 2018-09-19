function [result] = SetPWMFromThreadPololu(pPololu, channel, pw)
result = calllib('hardwarex', 'SetPWMFromThreadPololux', pPololu, channel, pw);
