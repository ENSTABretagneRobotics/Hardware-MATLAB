% Ideally, you should call :
% hardwarex_init
% in the beginning (otherwise the initialization will be done when necessary but might take several seconds), and :
% unloadlibrary('hardwarex');
% at the end (this will not be done automatically, unloadlibrary might fail if all the variables that use types from the library are not removed using clean...).
if not(libisloaded('hardwarex'))
    addpath(pwd); % Old MATLAB versions e.g. R2015b do not seem to always translate addpath('.') to an absolute path.
    switch (computer)
        case 'PCWIN64'
            addpath('x64');
            try
                %loadlibrary('hardwarex', @hardwarex_proto);
                [notfound,warnings]=loadlibrary('hardwarex', @hardwarex_proto);
            catch
                [notfound,warnings]=loadlibrary('hardwarex', 'hardwarex.h', 'includepath', 'MAVLinkSDK', 'includepath', 'C:\Program Files\MAVLinkSDK', 'includepath', 'C:\Program Files (x86)\MAVLinkSDK', 'includepath', 'SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'C:\Program Files\SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'C:\Program Files\SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'C:\Program Files (x86)\SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'C:\Program Files (x86)\SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'rplidar_sdk\sdk\include', 'includepath', 'rplidar_sdk\sdk\src', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\include', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\src', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\include', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\src', 'includepath', 'rplidar_sdk\sdk\sdk\include', 'includepath', 'rplidar_sdk\sdk\sdk\src', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\sdk\include', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\sdk\src', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\sdk\include', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\sdk\src', 'includepath', 'include');
            end
        case 'PCWIN'
            addpath('x86');
            try
                %loadlibrary('hardwarex');
                [notfound,warnings]=loadlibrary('hardwarex', @hardwarex_proto);
            catch
                [notfound,warnings]=loadlibrary('hardwarex', 'hardwarex.h', 'includepath', 'MAVLinkSDK', 'includepath', 'C:\Program Files\MAVLinkSDK', 'includepath', 'C:\Program Files (x86)\MAVLinkSDK', 'includepath', 'SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'C:\Program Files\SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'C:\Program Files\SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'C:\Program Files (x86)\SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'C:\Program Files (x86)\SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'rplidar_sdk\sdk\include', 'includepath', 'rplidar_sdk\sdk\src', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\include', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\src', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\include', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\src', 'includepath', 'rplidar_sdk\sdk\sdk\include', 'includepath', 'rplidar_sdk\sdk\sdk\src', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\sdk\include', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\sdk\src', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\sdk\include', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\sdk\src', 'includepath', 'include');
            end
        case 'MACI64'
            addpath('mac');
            try
                %loadlibrary('hardwarex');
                [notfound,warnings]=loadlibrary('hardwarex', @hardwarex_proto);
            catch
                [notfound,warnings]=loadlibrary('hardwarex', 'hardwarex.h', 'includepath', 'MAVLinkSDK', 'includepath', 'MAVLinkSDK/include', 'includepath', '/usr/local/include', 'includepath', 'sbgECom/src', 'includepath', 'sbgECom/common', 'includepath', 'SBG Systems/Inertial SDK/Software Development/sbgECom/src', 'includepath', 'SBG Systems/Inertial SDK/Software Development/sbgECom/common', 'includepath', '/usr/local/include/sbgECom/src', 'includepath', '/usr/local/include/sbgECom/common', 'includepath', 'rplidar_sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/src', 'includepath', 'rplidar_sdk/sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/src', 'includepath', 'include');
            end
        case 'MACA64'
            addpath('mac');
            try
                %loadlibrary('hardwarex');
                [notfound,warnings]=loadlibrary('hardwarex', @hardwarex_proto);
            catch
                [notfound,warnings]=loadlibrary('hardwarex', 'hardwarex.h', 'includepath', 'MAVLinkSDK', 'includepath', 'MAVLinkSDK/include', 'includepath', '/usr/local/include', 'includepath', 'sbgECom/src', 'includepath', 'sbgECom/common', 'includepath', 'SBG Systems/Inertial SDK/Software Development/sbgECom/src', 'includepath', 'SBG Systems/Inertial SDK/Software Development/sbgECom/common', 'includepath', '/usr/local/include/sbgECom/src', 'includepath', '/usr/local/include/sbgECom/common', 'includepath', 'rplidar_sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/src', 'includepath', 'rplidar_sdk/sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/src', 'includepath', 'include');
            end
        case 'GLNXA64'
            addpath('linux_x64');
            try
                %loadlibrary('hardwarex');
                [notfound,warnings]=loadlibrary('hardwarex', @hardwarex_proto);
            catch
                [notfound,warnings]=loadlibrary('hardwarex', 'hardwarex.h', 'includepath', 'MAVLinkSDK', 'includepath', 'MAVLinkSDK/include', 'includepath', '/usr/local/include', 'includepath', 'sbgECom/src', 'includepath', 'sbgECom/common', 'includepath', 'SBG Systems/Inertial SDK/Software Development/sbgECom/src', 'includepath', 'SBG Systems/Inertial SDK/Software Development/sbgECom/common', 'includepath', '/usr/local/include/sbgECom/src', 'includepath', '/usr/local/include/sbgECom/common', 'includepath', 'rplidar_sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/src', 'includepath', 'rplidar_sdk/sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/src', 'includepath', 'include');
            end
        otherwise
            try
                %loadlibrary('hardwarex');
                [notfound,warnings]=loadlibrary('hardwarex', @hardwarex_proto);
            catch
                [notfound,warnings]=loadlibrary('hardwarex', 'hardwarex.h', 'includepath', 'MAVLinkSDK', 'includepath', 'MAVLinkSDK/include', 'includepath', '/usr/local/include', 'includepath', 'sbgECom/src', 'includepath', 'sbgECom/common', 'includepath', 'SBG Systems/Inertial SDK/Software Development/sbgECom/src', 'includepath', 'SBG Systems/Inertial SDK/Software Development/sbgECom/common', 'includepath', '/usr/local/include/sbgECom/src', 'includepath', '/usr/local/include/sbgECom/common', 'includepath', 'rplidar_sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/src', 'includepath', 'rplidar_sdk/sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/src', 'includepath', 'include');
            end
    end
    %libfunctions hardwarex -full
end
