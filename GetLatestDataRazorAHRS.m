function [result, razorahrsdata] = GetLatestDataRazorAHRS(pRazorAHRS)

pRazorAHRSData_p = calllib('hardwarex', 'CreateRazorAHRSDatax');

result = calllib('hardwarex', 'GetLatestDataRazorAHRSx', pRazorAHRS, pRazorAHRSData_p);

razorahrsdata = pRazorAHRSData_p.value;

calllib('hardwarex', 'DestroyRazorAHRSDatax', pRazorAHRSData_p);
