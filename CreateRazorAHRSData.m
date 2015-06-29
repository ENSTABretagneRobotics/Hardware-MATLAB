function pRazorAHRSData = CreateRazorAHRSData()

% Ideally, user should load manually...
hardwarex_init;

pRazorAHRSData = calllib('hardwarex', 'CreateRazorAHRSDatax');
