function [result] = DisconnectMDM(pMDM)
result = calllib('hardwarex', 'DisconnectMDMx', pMDM);
