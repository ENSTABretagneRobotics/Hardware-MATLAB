function [result, razorahrsdata] = GetLatestDataFromThreadRazorAHRS(pRazorAHRS)

pRazorAHRSData_p = calllib('hardwarex', 'CreateRazorAHRSDatax');

result = calllib('hardwarex', 'GetLatestDataFromThreadRazorAHRSx', pRazorAHRS, pRazorAHRSData_p);

razorahrsdata = pRazorAHRSData_p.value;

calllib('hardwarex', 'DestroyRazorAHRSDatax', pRazorAHRSData_p);
