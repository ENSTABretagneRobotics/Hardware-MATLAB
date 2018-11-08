function [result, pressure] = GetPressureFromThreadP33x(pP33x)

pressure = 0;
pPressure = libpointer('doublePtr', pressure);

result = calllib('hardwarex', 'GetPressureFromThreadP33xx', pP33x, pPressure);

pressure = pPressure.value;
