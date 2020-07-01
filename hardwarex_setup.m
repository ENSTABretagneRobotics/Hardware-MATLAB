% Run this file to make MATLAB 64 bit generate important precompiled files :
% hardwarex_proto.m and hardwarex_thunk_pcwin64.dll.
% Visual Studio with 64 bit compiler needs to be installed and
% correctly configured in MATLAB (using mex -setup and mex -setup C++ in
% MATLAB).
% These files will be necessary for MATLAB 64 bit users that do not have
% Visual Studio (they should be provided in the x64 folder).
% Note that this problem does not exist for MATLAB 32 bit (for several
% reasons, such as the fact that it is provided with a 32 bit internal
% compiler and therefore do not need Visual Studio...).
addpath('.');
switch (computer)
    case 'PCWIN64'
        addpath('x64');
        %loadlibrary('hardwarex', 'hardwarex.h', 'notempdir')
        loadlibrary('hardwarex', 'hardwarex.h', 'notempdir', 'includepath', 'MAVLinkSDK', 'includepath', 'C:\Program Files\MAVLinkSDK', 'includepath', 'C:\Program Files (x86)\MAVLinkSDK', 'includepath', 'SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'C:\Program Files\SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'C:\Program Files\SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'C:\Program Files (x86)\SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'C:\Program Files (x86)\SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'rplidar_sdk\sdk\sdk\include', 'includepath', 'rplidar_sdk\sdk\sdk\src', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\sdk\include', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\sdk\src', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\sdk\include', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\sdk\src');
    case 'PCWIN'
        addpath('x86');
        loadlibrary('hardwarex', 'hardwarex.h', 'notempdir', 'includepath', 'MAVLinkSDK', 'includepath', 'C:\Program Files\MAVLinkSDK', 'includepath', 'C:\Program Files (x86)\MAVLinkSDK', 'includepath', 'SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'C:\Program Files\SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'C:\Program Files\SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'C:\Program Files (x86)\SBG Systems\Inertial SDK\Software Development\sbgECom\src', 'includepath', 'C:\Program Files (x86)\SBG Systems\Inertial SDK\Software Development\sbgECom\common', 'includepath', 'rplidar_sdk\sdk\sdk\include', 'includepath', 'rplidar_sdk\sdk\sdk\src', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\sdk\include', 'includepath', 'C:\Program Files\rplidar_sdk\sdk\sdk\src', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\sdk\include', 'includepath', 'C:\Program Files (x86)\rplidar_sdk\sdk\sdk\src');
    otherwise
        loadlibrary('hardwarex', 'hardwarex.h', 'notempdir', 'includepath', 'MAVLinkSDK', 'includepath', '/usr/local/include', 'includepath', 'sbgECom/src', 'includepath', 'sbgECom/common', 'includepath', '/usr/local/include/sbgECom/src', 'includepath', '/usr/local/include/sbgECom/common', 'includepath', 'rplidar_sdk/sdk/sdk/include', 'includepath', 'rplidar_sdk/sdk/sdk/src', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/include', 'includepath', '/usr/local/include/rplidar_sdk/sdk/sdk/src');
end
%libfunctions hardwarex -full
