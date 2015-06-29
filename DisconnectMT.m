function [result] = DisconnectMT(pMT)
result = calllib('hardwarex', 'DisconnectMTx', pMT);
