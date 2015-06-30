function [result] = SetPWMFromThreadMaestro(pMaestro, channel, pw)
result = calllib('hardwarex', 'SetPWMFromThreadMaestrox', pMaestro, channel, pw);
