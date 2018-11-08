function [result] = ConnectMDM(pMDM, szCfgFilePath)
result = calllib('hardwarex', 'ConnectMDMx', pMDM, szCfgFilePath);
