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
switch (computer)
    case 'PCWIN64'
        %loadlibrary('hardwarex', 'hardwarex.h', 'notempdir')
        loadlibrary('hardwarex', 'hardwarex.h', 'notempdir', 'includepath', 'C:\Program Files\MAVLinkSDK', 'includepath', 'C:\Program Files (x86)\MAVLinkSDK', 'includepath', 'MAVLinkSDK')
    case 'PCWIN'
        loadlibrary('hardwarex', 'hardwarex.h', 'notempdir', 'includepath', 'C:\Program Files\MAVLinkSDK', 'includepath', 'C:\Program Files (x86)\MAVLinkSDK', 'includepath', 'MAVLinkSDK')
    otherwise
        loadlibrary('hardwarex', 'hardwarex.h', 'notempdir', 'includepath', 'MAVLinkSDK')
end
%libfunctions hardwarex -full
