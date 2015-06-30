function pMaestro = CreateMaestro()

% Ideally, user should load manually...
hardwarex_init;

pMaestro = calllib('hardwarex', 'CreateMaestrox');
