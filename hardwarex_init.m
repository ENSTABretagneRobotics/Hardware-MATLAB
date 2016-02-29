% Ideally, you should call :
% hardwarex_init
% in the beginning (otherwise the initialization will be done when necessary but might take several seconds), and :
% unloadlibrary('hardwarex');
% at the end (this will not be done automatically, unloadlibrary might fail if all the variables that use types from the library are not removed using clean...).
if not(libisloaded('hardwarex'))
    switch (computer)
        case 'PCWIN64'
            %loadlibrary('hardwarex', @hardwarex_proto);
            loadlibrary('hardwarex', @hardwarex_proto, 'includepath', 'C:\Program Files\MAVLinkSDK', 'includepath', 'C:\Program Files (x86)\MAVLinkSDK', 'includepath', 'MAVLinkSDK');
            %libfunctions hardwarex -full
        otherwise
            %loadlibrary('hardwarex');
            loadlibrary('hardwarex', 'hardwarex.h', 'includepath', 'C:\Program Files\MAVLinkSDK', 'includepath', 'C:\Program Files (x86)\MAVLinkSDK', 'includepath', 'MAVLinkSDK');
            %libfunctions hardwarex -full
    end
end
