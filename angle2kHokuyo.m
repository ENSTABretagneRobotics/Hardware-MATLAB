function [k] = angle2kHokuyo(pHokuyo, angle)
k = calllib('hardwarex', 'angle2kHokuyox', pHokuyo, angle);
