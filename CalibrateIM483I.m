function [result] = CalibrateIM483I(pIM483I)
result = calllib('hardwarex', 'CalibrateIM483Ix', pIM483I);
