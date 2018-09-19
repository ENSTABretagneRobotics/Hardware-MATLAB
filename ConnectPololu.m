function [result] = ConnectPololu(pPololu, szCfgFilePath)
result = calllib('hardwarex', 'ConnectPololux', pPololu, szCfgFilePath);
