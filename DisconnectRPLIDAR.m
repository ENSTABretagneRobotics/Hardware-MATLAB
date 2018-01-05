function [result] = DisconnectRPLIDAR(pRPLIDAR)
result = calllib('hardwarex', 'DisconnectRPLIDARx', pRPLIDAR);
