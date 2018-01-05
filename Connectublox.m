function [result] = Connectublox(publox, szCfgFilePath)
result = calllib('hardwarex', 'Connectubloxx', publox, szCfgFilePath);
