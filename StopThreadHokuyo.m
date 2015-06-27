function [result] = StopThreadHokuyo(pHokuyo)
result = calllib('hardwarex', 'StopThreadHokuyox', pHokuyo);
