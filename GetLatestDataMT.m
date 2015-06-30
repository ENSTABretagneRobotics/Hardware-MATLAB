function [result, mtdata] = GetLatestDataMT(pMT)

pMTData = calllib('hardwarex', 'CreateMTDatax');

result = calllib('hardwarex', 'GetLatestDataMTx', pMT, pMTData);

mtdata = pMTData.value;

calllib('hardwarex', 'DestroyMTDatax', pMTData);
