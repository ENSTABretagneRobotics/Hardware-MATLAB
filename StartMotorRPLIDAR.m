function [result] = StartMotorRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'StartMotorRPLIDARx', pRPLIDAR);
