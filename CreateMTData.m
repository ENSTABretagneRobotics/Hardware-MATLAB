function pMTData = CreateMTData()

% Ideally, user should load manually...
hardwarex_init;

pMTData = calllib('hardwarex', 'CreateMTDatax');
