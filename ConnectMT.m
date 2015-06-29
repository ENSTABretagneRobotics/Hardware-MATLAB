function [result] = ConnectMT(pMT, szCfgFilePath)
result = calllib('hardwarex', 'ConnectMTx', pMT, szCfgFilePath);
