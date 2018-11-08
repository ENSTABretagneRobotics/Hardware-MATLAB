function [result] = SetMotorTorqueIM483I(pIM483I, percent)
result = calllib('hardwarex', 'SetMotorTorqueIM483Ix', pIM483I, percent);
