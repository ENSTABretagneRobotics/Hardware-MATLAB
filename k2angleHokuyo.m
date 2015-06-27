function [angle] = k2angleHokuyo(pHokuyo, k)
angle = calllib('hardwarex', 'k2angleHokuyox', pHokuyo, k);
