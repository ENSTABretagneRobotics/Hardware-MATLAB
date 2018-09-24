function [result] = SetPWMJrkPololu(pPololu, pw)
result = calllib('hardwarex', 'SetPWMJrkPololux', pPololu, pw);
