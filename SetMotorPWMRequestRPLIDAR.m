function [result] = SetMotorPWMRequestRPLIDAR(pRPLIDAR, pwm)
result = calllib('hardwarex', 'SetMotorPWMRequestRPLIDARx', pRPLIDAR, pwm);
