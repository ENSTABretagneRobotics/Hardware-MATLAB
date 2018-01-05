function [result, nmeadata] = GetNMEASentenceFromThreadublox(publox)

pNMEAData = calllib('hardwarex', 'CreateNMEADatax');

result = calllib('hardwarex', 'GetNMEASentenceFromThreadubloxx', publox, pNMEAData);

nmeadata = pNMEAData.value;

calllib('hardwarex', 'DestroyNMEADatax', pNMEAData);
