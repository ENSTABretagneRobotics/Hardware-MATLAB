function pMDM = CreateMDM()

% Ideally, user should load manually...
hardwarex_init;

pMDM = calllib('hardwarex', 'CreateMDMx');
