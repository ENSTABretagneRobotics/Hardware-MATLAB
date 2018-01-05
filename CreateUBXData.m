function pUBXData = CreateUBXData()

% Ideally, user should load manually...
hardwarex_init;

pUBXData = calllib('hardwarex', 'CreateUBXDatax');
