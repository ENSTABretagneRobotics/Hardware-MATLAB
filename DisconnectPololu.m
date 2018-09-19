function [result] = DisconnectPololu(pPololu)
result = calllib('hardwarex', 'DisconnectPololux', pPololu);
