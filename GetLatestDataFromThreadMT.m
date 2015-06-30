function [result, mtdata] = GetLatestDataFromThreadMT(pMT)

pMTData = calllib('hardwarex', 'CreateMTDatax');

result = calllib('hardwarex', 'GetLatestDataFromThreadMTx', pMT, pMTData);

mtdata = pMTData.value;

calllib('hardwarex', 'DestroyMTDatax', pMTData);
