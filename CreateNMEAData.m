function pNMEAData = CreateNMEAData()

% Ideally, user should load manually...
hardwarex_init;

pNMEAData = calllib('hardwarex', 'CreateNMEADatax');
