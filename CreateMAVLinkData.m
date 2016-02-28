function pMAVLinkData = CreateMAVLinkData()

% Ideally, user should load manually...
hardwarex_init;

pMAVLinkData = calllib('hardwarex', 'CreateMAVLinkDatax');
