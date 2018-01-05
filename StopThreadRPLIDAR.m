function [result] = StopThreadRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StopThreadRPLIDARx', pRPLIDAR);
