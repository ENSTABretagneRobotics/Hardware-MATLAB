function pRPLIDAR = CreateRPLIDAR()

% Ideally, user should load manually...
hardwarex_init;

pRPLIDAR = calllib('hardwarex', 'CreateRPLIDARx');
