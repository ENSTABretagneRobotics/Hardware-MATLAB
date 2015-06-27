function [result] = DisconnectHokuyo(pHokuyo)
result = calllib('hardwarex', 'DisconnectHokuyox', pHokuyo);
