MAVLink support
===============
Windows : 
- In hardwarex.h, uncomment #define ENABLE_MAVLINK_SUPPORT.
- In MATLAB (requires 2014a or later), run mex -setup and mex -setup C++ and choose Visual Studio 2013 or later.
- Replace ..\x86 and ..\x64 folders with the ones in this folder.
- Copy the headers from https://github.com/mavlink/c_library in C:\Program Files (x86)\MAVLinkSDK\mavlink for a 64 bit version of Windows or C:\Program Files\MAVLinkSDK\mavlink for a 32 bit version of Windows.
- Follow ../ReadMe.txt

Linux/Mac : 
- In hardwarex.h, uncomment #define ENABLE_MAVLINK_SUPPORT.
- Copy the headers from https://github.com/mavlink/c_library in /usr/local/include/mavlink.
- Follow ../ReadMe.txt
