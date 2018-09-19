function [result] = StopScanThreadRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StopScanThreadRPLIDARx', pRPLIDAR);
