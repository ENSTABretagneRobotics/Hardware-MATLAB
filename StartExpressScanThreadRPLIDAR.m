function [result] = StartExpressScanThreadRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StartExpressScanThreadRPLIDARx', pRPLIDAR);
