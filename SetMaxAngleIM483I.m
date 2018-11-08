function [result] = SetMaxAngleIM483I(pIM483I, angle)
result = calllib('hardwarex', 'SetMaxAngleIM483Ix', pIM483I, angle);
