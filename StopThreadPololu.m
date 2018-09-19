function [result] = StopThreadPololu(pPololu)
result = calllib('hardwarex', 'StopThreadPololux', pPololu);
