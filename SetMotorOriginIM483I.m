function [result] = SetMotorOriginIM483I(pIM483I)
result = calllib('hardwarex', 'SetMotorOriginIM483Ix', pIM483I);
