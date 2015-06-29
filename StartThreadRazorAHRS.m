function [result] = StartThreadRazorAHRS(pRazorAHRS)
result = calllib('hardwarex', 'StartThreadRazorAHRSx', pRazorAHRS);
