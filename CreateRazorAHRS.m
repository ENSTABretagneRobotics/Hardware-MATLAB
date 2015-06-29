function pRazorAHRS = CreateRazorAHRS()

% Ideally, user should load manually...
hardwarex_init;

pRazorAHRS = calllib('hardwarex', 'CreateRazorAHRSx');
