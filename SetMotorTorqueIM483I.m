function [result] = SetMotorTorqueIM483I(pIM483I, holdpercent, runpercent)
result = calllib('hardwarex', 'SetMotorTorqueIM483Ix', pIM483I, holdpercent, runpercent);
