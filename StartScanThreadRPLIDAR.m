function [result] = StartScanThreadRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StartScanThreadRPLIDARx', pRPLIDAR);
