function [result] = PurgeDataMDM(pMDM)
result = calllib('hardwarex', 'PurgeDataMDMx', pMDM);
