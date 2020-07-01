function [result] = StopRequestRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StopRequestRPLIDARx', pRPLIDAR);
