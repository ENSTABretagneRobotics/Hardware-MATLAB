function [result] = DisconnectP33x(pP33x)
result = calllib('hardwarex', 'DisconnectP33xx', pP33x);
