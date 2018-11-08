function pP33x = CreateP33x()

% Ideally, user should load manually...
hardwarex_init;

pP33x = calllib('hardwarex', 'CreateP33xx');
