function [result] = ConnectP33x(pP33x, szCfgFilePath)
result = calllib('hardwarex', 'ConnectP33xx', pP33x, szCfgFilePath);
