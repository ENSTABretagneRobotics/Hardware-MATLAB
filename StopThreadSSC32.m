function [result] = StopThreadSSC32(pSSC32)
result = calllib('hardwarex', 'StopThreadSSC32x', pSSC32);
