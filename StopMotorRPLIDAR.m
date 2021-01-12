function [result] = StopMotorRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StopMotorRPLIDARx', pRPLIDAR);
