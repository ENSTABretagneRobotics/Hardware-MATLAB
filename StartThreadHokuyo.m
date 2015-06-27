function [result] = StartThreadHokuyo(pHokuyo)
result = calllib('hardwarex', 'StartThreadHokuyox', pHokuyo);
