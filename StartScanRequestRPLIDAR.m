function [result] = StartScanRequestRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StartScanRequestRPLIDARx', pRPLIDAR);
