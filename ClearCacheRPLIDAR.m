function [result] = ClearCacheRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'ClearCacheRPLIDARx', pRPLIDAR);
