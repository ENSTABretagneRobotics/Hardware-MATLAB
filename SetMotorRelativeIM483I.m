function [result] = SetMotorRelativeIM483I(pIM483I, val, bForce)
result = calllib('hardwarex', 'SetMotorRelativeIM483Ix', pIM483I, val, bForce);
