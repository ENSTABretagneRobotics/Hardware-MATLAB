function [result] = ConnectMaestro(pMaestro, szCfgFilePath)
result = calllib('hardwarex', 'ConnectMaestrox', pMaestro, szCfgFilePath);
