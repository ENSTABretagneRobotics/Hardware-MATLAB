function [result] = StopThreadSBG(pSBG)
result = calllib('hardwarex', 'StopThreadSBGx', pSBG);
