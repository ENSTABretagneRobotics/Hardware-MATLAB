function [result] = StartOtherScanRequestRPLIDAR(pRPLIDAR, scanmode)
result = calllib('hardwarex', 'StartOtherScanRequestRPLIDARx', pRPLIDAR, scanmode);
