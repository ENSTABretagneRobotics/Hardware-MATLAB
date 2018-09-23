function [result, sbgdata] = GetLatestDataFromThreadSBG(pSBG)

pSBGData = calllib('hardwarex', 'CreateSBGDatax');

result = calllib('hardwarex', 'GetLatestDataFromThreadSBGx', pSBG, pSBGData);

sbgdata = pSBGData.value;

calllib('hardwarex', 'DestroySBGDatax', pSBGData);
