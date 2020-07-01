function [result] = StartForceScanRequestRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StartForceScanRequestRPLIDARx', pRPLIDAR);
