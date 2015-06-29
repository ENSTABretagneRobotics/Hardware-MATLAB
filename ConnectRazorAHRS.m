function [result] = ConnectRazorAHRS(pRazorAHRS, szCfgFilePath)
result = calllib('hardwarex', 'ConnectRazorAHRSx', pRazorAHRS, szCfgFilePath);
