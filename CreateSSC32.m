function pSSC32 = CreateSSC32()

% Ideally, user should load manually...
hardwarex_init;

pSSC32 = calllib('hardwarex', 'CreateSSC32x');
