function [result] = SetPWMPololu(pPololu, channel, pw)
result = calllib('hardwarex', 'SetPWMPololux', pPololu, channel, pw);
