function [result, nmeadata] = GetNMEASentenceublox(publox)

pNMEAData = calllib('hardwarex', 'CreateNMEADatax');

result = calllib('hardwarex', 'GetNMEASentenceubloxx', publox, pNMEAData);

nmeadata = pNMEAData.value;

calllib('hardwarex', 'DestroyNMEADatax', pNMEAData);
