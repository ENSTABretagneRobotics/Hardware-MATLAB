function [result] = StartOtherScanThreadRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StartOtherScanThreadRPLIDARx', pRPLIDAR);
