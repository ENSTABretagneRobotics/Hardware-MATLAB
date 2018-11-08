function [result, temperature] = GetTemperatureFromThreadP33x(pP33x)

temperature = 0;
pTemperature = libpointer('doublePtr', temperature);

result = calllib('hardwarex', 'GetTemperatureFromThreadP33xx', pP33x, pTemperature);

temperature = pTemperature.value;
