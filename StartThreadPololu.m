function [result] = StartThreadPololu(pPololu)
result = calllib('hardwarex', 'StartThreadPololux', pPololu);
