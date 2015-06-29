function pMT = CreateMT()

% Ideally, user should load manually...
hardwarex_init;

pMT = calllib('hardwarex', 'CreateMTx');
