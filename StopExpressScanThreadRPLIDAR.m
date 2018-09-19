function [result] = StopExpressScanThreadRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StopExpressScanThreadRPLIDARx', pRPLIDAR);
