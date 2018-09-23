function pSBGData = CreateSBGData()

% Ideally, user should load manually...
hardwarex_init;

pSBGData = calllib('hardwarex', 'CreateSBGDatax');
