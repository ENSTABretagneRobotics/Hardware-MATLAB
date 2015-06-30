function [result, razorahrsdata] = GetLatestDataRazorAHRS(pRazorAHRS)

pRazorAHRSData = calllib('hardwarex', 'CreateRazorAHRSDatax');

result = calllib('hardwarex', 'GetLatestDataRazorAHRSx', pRazorAHRS, pRazorAHRSData);

razorahrsdata = pRazorAHRSData.value;

calllib('hardwarex', 'DestroyRazorAHRSDatax', pRazorAHRSData);
