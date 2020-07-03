% Ideally, you should call :
% hardwarex_init
% in the beginning (otherwise the initialization will be done when necessary but might take several seconds), and :
% unloadlibrary('hardwarex');
% at the end (this will not be done automatically, unloadlibrary might fail if all the variables that use types from the library are not removed using clean...).
if not(libisloaded('hardwarex'))
    addpath('.');
    switch (computer)
        case 'PCWIN64'
            addpath('x64');
            %loadlibrary('hardwarex', @hardwarex_proto);
            [notfound,warnings]=loadlibrary('hardwarex', @hardwarex_proto);
        case 'PCWIN'
            addpath('x86');
            %loadlibrary('hardwarex');
            [notfound,warnings]=loadlibrary('hardwarex', @hardwarex_proto);
        otherwise
            %loadlibrary('hardwarex');
            [notfound,warnings]=loadlibrary('hardwarex', 'hardwarex.h', 'includepath', 'MAVLinkSDK', 'includepath', '/usr/local/include', 'includepath', 'sbgECom/src', 'includepath', 'sbgECom/common', 'includepath', '/usr/local/include/sbgECom/src', 'includepath', '/usr/local/include/sbgECom/common', 'includepath', 'rplidar_sdk/sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/src');
    end
    %libfunctions hardwarex -full
end
