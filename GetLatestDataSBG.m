function [result, sbgdata] = GetLatestDataSBG(pSBG)

pSBGData = calllib('hardwarex', 'CreateSBGDatax');

result = calllib('hardwarex', 'GetLatestDataSBGx', pSBG, pSBGData);

sbgdata = pSBGData.value;

calllib('hardwarex', 'DestroySBGDatax', pSBGData);
