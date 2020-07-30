function [result] = StopOtherScanThreadRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StopOtherScanThreadRPLIDARx', pRPLIDAR);
