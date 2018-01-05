function publox = Createublox()

% Ideally, user should load manually...
hardwarex_init;

publox = calllib('hardwarex', 'Createubloxx');
