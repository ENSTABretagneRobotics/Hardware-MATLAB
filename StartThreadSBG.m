function [result] = StartThreadSBG(pSBG)
result = calllib('hardwarex', 'StartThreadSBGx', pSBG);
