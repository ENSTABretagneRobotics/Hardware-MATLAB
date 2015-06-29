function [result] = StartThreadMT(pMT)
result = calllib('hardwarex', 'StartThreadMTx', pMT);
