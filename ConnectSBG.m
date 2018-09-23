function [result] = ConnectSBG(pSBG, szCfgFilePath)
result = calllib('hardwarex', 'ConnectSBGx', pSBG, szCfgFilePath);
