function pSBG = CreateSBG()

% Ideally, user should load manually...
hardwarex_init;

pSBG = calllib('hardwarex', 'CreateSBGx');
