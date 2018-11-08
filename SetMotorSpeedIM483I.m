function [result] = SetMotorSpeedIM483I(pIM483I, val)
result = calllib('hardwarex', 'SetMotorSpeedIM483Ix', pIM483I, val);
