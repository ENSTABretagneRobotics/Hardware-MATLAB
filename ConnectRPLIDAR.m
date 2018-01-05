function [result] = ConnectRPLIDAR(pRPLIDAR, szCfgFilePath)
result = calllib('hardwarex', 'ConnectRPLIDARx', pRPLIDAR, szCfgFilePath);
