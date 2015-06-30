function [result] = DisconnectSSC32(pSSC32)
result = calllib('hardwarex', 'DisconnectSSC32x', pSSC32);
