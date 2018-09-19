function pPololu = CreatePololu()

% Ideally, user should load manually...
hardwarex_init;

pPololu = calllib('hardwarex', 'CreatePololux');
