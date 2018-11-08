function [result, pressure] = GetPressureP33x(pP33x)

pressure = 0;
pPressure = libpointer('doublePtr', pressure);

result = calllib('hardwarex', 'GetPressureP33xx', pP33x, pPressure);

pressure = pPressure.value;
