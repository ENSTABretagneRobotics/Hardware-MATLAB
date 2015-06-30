function [result, razorahrsdata] = GetLatestDataFromThreadRazorAHRS(pRazorAHRS)

pRazorAHRSData = calllib('hardwarex', 'CreateRazorAHRSDatax');

result = calllib('hardwarex', 'GetLatestDataFromThreadRazorAHRSx', pRazorAHRS, pRazorAHRSData);

razorahrsdata = pRazorAHRSData.value;

calllib('hardwarex', 'DestroyRazorAHRSDatax', pRazorAHRSData);
