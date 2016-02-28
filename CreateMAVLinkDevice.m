function pMAVLinkDevice = CreateMAVLinkDevice()

% Ideally, user should load manually...
hardwarex_init;

pMAVLinkDevice = calllib('hardwarex', 'CreateMAVLinkDevicex');
