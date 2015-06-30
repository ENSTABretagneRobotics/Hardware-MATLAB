function [result] = ConnectSSC32(pSSC32, szCfgFilePath)
result = calllib('hardwarex', 'ConnectSSC32x', pSSC32, szCfgFilePath);
