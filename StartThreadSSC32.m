function [result] = StartThreadSSC32(pSSC32)
result = calllib('hardwarex', 'StartThreadSSC32x', pSSC32);
