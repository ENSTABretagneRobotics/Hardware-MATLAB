function [result, mtdata] = GetLatestDataFromThreadMT(pMT)

pMTData_p = calllib('hardwarex', 'CreateMTDatax');

result = calllib('hardwarex', 'GetLatestDataFromThreadMTx', pMT, pMTData_p);

mtdata = pMTData_p.value;

calllib('hardwarex', 'DestroyMTDatax', pMTData_p);
