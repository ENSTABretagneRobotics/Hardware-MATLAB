function [result, mtdata] = GetLatestDataMT(pMT)

pMTData_p = calllib('hardwarex', 'CreateMTDatax');

result = calllib('hardwarex', 'GetLatestDataMTx', pMT, pMTData_p);

mtdata = pMTData_p.value;

calllib('hardwarex', 'DestroyMTDatax', pMTData_p);
