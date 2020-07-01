function [result] = StartExpressScanRequestRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StartExpressScanRequestRPLIDARx', pRPLIDAR);
