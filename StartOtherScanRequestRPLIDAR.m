function [result] = StartOtherScanRequestRPLIDAR(pRPLIDAR, scanmodeid)
result = calllib('hardwarex', 'StartOtherScanRequestRPLIDARx', pRPLIDAR, scanmodeid);
