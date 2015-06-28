function pNMEADevice = CreateNMEADevice()

% Ideally, user should load manually...
hardwarex_init;

pNMEADevice = calllib('hardwarex', 'CreateNMEADevicex');
