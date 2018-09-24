function [result, pw] = GetPWMSSC32(pSSC32, channel)

pw = 0;
pPw = libpointer('int32Ptr', pw);

result = calllib('hardwarex', 'GetPWMSSC32x', pSSC32, channel, pPw);

pw = pPw.value;
