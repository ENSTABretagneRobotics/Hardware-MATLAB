MAVLink and SBG support
===============
Windows : 
- In hardwarex.h, check that #define ENABLE_MAVLINK_SUPPORT and ENABLE_SBG_SUPPORT are uncommented.
- Copy the headers from https://github.com/mavlink/c_library_v1/archive/0fc203298923f1d7c225cc6f43918d6663809e38.zip in C:\Program Files (x86)\MAVLinkSDK\mavlink for a 64 bit version of Windows or C:\Program Files\MAVLinkSDK\mavlink for a 32 bit version of Windows (or in ..\MAVLinkSDK\mavlink).
- Copy the files from http://www.ensta-bretagne.fr/lebars/Share/SBG.zip in C:\Program Files (x86) for a 64 bit version of Windows or C:\Program Files for a 32 bit version of Windows (or in ..).
- Rebuild using Visual Studio 2012 or later and put the resulting hardwarex.dll in the corresponding ..\x86 and ..\x64 folders.
- In MATLAB, run mex -setup and mex -setup C++ and choose Visual Studio 2013 or later.
- Run hardwarex_setup.m and put the resulting hardwarex_proto.m and hardwarex_thunk_pcwin64.dll in the corresponding ..\x86 and ..\x64 folders.
- Follow ..\ReadMe.txt

Linux/Mac : 
- In hardwarex.h, check that #define ENABLE_MAVLINK_SUPPORT and ENABLE_SBG_SUPPORT are uncommented.
- In the Makefile, check that LDFLAGS += -lsbgECom is uncommented.
- Copy the headers from https://github.com/mavlink/c_library_v1/archive/0fc203298923f1d7c225cc6f43918d6663809e38.zip in /usr/local/include/mavlink (or ../MAVLinkSDK/mavlink).
- Copy sbgECom folder from http://www.ensta-bretagne.fr/lebars/Share/SBG.zip in /usr/local/include (or ..).
- Follow ../ReadMe.txt
