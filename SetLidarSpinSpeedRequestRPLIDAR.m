function [result] = SetLidarSpinSpeedRequestRPLIDAR(pRPLIDAR, rpm)
result = calllib('hardwarex', 'SetLidarSpinSpeedRequestRPLIDARx', pRPLIDAR, rpm);
