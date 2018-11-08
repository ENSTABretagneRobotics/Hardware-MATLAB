function [result, temperature] = GetTemperatureP33x(pP33x)

temperature = 0;
pTemperature = libpointer('doublePtr', temperature);

result = calllib('hardwarex', 'GetTemperatureP33xx', pP33x, pTemperature);

temperature = pTemperature.value;
