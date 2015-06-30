function [result] = SetPWMMaestro(pMaestro, channel, pw)
result = calllib('hardwarex', 'SetPWMMaestrox', pMaestro, channel, pw);
