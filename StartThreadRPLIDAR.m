function [result] = StartThreadRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StartThreadRPLIDARx', pRPLIDAR);
