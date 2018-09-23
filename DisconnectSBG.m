function [result] = DisconnectSBG(pSBG)
result = calllib('hardwarex', 'DisconnectSBGx', pSBG);
