function [result] = SetMaxAngleFromThreadIM483I(pIM483I, angle)
result = calllib('hardwarex', 'SetMaxAngleFromThreadIM483Ix', pIM483I, angle);
