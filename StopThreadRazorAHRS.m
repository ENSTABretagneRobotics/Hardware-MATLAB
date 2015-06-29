function [result] = StopThreadRazorAHRS(pRazorAHRS)
result = calllib('hardwarex', 'StopThreadRazorAHRSx', pRazorAHRS);
