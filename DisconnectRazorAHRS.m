function [result] = DisconnectRazorAHRS(pRazorAHRS)
result = calllib('hardwarex', 'DisconnectRazorAHRSx', pRazorAHRS);
