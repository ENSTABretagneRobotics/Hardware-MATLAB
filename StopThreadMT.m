function [result] = StopThreadMT(pMT)
result = calllib('hardwarex', 'StopThreadMTx', pMT);
