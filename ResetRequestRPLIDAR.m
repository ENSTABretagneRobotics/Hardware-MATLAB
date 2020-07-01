function [result] = ResetRequestRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'ResetRequestRPLIDARx', pRPLIDAR);
