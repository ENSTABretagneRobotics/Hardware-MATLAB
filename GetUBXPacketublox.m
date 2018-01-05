function [result, ubxdata] = GetUBXPacketublox(publox)

pUBXData = calllib('hardwarex', 'CreateUBXDatax');

result = calllib('hardwarex', 'GetUBXPacketubloxx', publox, pUBXData);

ubxdata = pUBXData.value;

calllib('hardwarex', 'DestroyUBXDatax', pUBXData);
