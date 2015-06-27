function [result] = ConnectHokuyo(pHokuyo, szCfgFilePath)
result = calllib('hardwarex', 'ConnectHokuyox', pHokuyo, szCfgFilePath);
