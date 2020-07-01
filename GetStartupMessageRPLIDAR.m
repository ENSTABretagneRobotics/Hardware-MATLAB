function [result] = GetStartupMessageRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'GetStartupMessageRPLIDARx', pRPLIDAR);
