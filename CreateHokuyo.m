function pHokuyo = CreateHokuyo()

% Ideally, user should load manually...
hardwarex_init;

pHokuyo = calllib('hardwarex', 'CreateHokuyox');
