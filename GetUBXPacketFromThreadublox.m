function [result, ubxdata] = GetUBXPacketFromThreadublox(publox)

pUBXData = calllib('hardwarex', 'CreateUBXDatax');

result = calllib('hardwarex', 'GetUBXPacketFromThreadubloxx', publox, pUBXData);

ubxdata = pUBXData.value;

calllib('hardwarex', 'DestroyUBXDatax', pUBXData);
