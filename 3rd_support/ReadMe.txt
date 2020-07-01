MAVLink, SBG, RPLIDAR SDK support (if needed to rebuild)
===============
Windows : 
- In `hardwarex.h`, check that `#define ENABLE_MAVLINK_SUPPORT`, `#define ENABLE_SBG_SUPPORT`, `#define ENABLE_RPLIDAR_SDK_SUPPORT` are uncommented.
- Copy the headers from https://github.com/mavlink/c_library_v1/archive/0fc203298923f1d7c225cc6f43918d6663809e38.zip in `C:\Program Files (x86)\MAVLinkSDK\mavlink` for a 64 bit version of Windows or `C:\Program Files\MAVLinkSDK\mavlink` for a 32 bit version of Windows (or in `..\MAVLinkSDK\mavlink`).
- Copy the files from https://www.ensta-bretagne.fr/lebars/Share/SBG%20Systems.zip and https://github.com/lebarsfa/rplidar_sdk (rebuild this one using Visual Studio 2010 or later or get a prebuilt version for Visual Studio 2017 on https://www.ensta-bretagne.fr/lebars/Share/rplidar_sdk.zip) in `C:\Program Files (x86)` for a 64 bit version of Windows or `C:\Program Files` for a 32 bit version of Windows (or in `..`).
- Rebuild using Visual Studio 2012 or later and put the resulting hardwarex.dll in the corresponding `..\x86` and `..\x64` folders.
- In MATLAB, run `mex -setup` and `mex -setup C++` and choose Visual Studio 2013 or later.
- Run `hardwarex_setup.m` and put the resulting `hardwarex_proto.m` and `hardwarex_thunk_pcwin64.dll` in the corresponding `..\x86` and `..\x64` folders (at this step `#define ENABLE_RPLIDAR_SDK_SUPPORT` might need to be commented in `hardwarex.h`...).
- Follow `..\ReadMe.txt`

Linux/Mac OS : 
- In `hardwarex.h`, check that `#define ENABLE_MAVLINK_SUPPORT`, `#define ENABLE_SBG_SUPPORT`, `#define ENABLE_RPLIDAR_SDK_SUPPORT` are uncommented.
- In the `Makefile`, check that `LDFLAGS += -lsbgECom -lrplidar_sdk` is uncommented.
- For Mac OS, you might want to install Homebrew and wget : 
	/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	brew install wget
- Copy the headers from https://github.com/mavlink/c_library_v1/archive/0fc203298923f1d7c225cc6f43918d6663809e38.zip in `/usr/local/include/mavlink` (or `../MAVLinkSDK/mavlink`) :
	wget https://github.com/mavlink/c_library_v1/archive/0fc203298923f1d7c225cc6f43918d6663809e38.zip
	unzip 0fc203298923f1d7c225cc6f43918d6663809e38.zip
	sudo mv c_library_v1-0fc203298923f1d7c225cc6f43918d6663809e38/ /usr/local/include/mavlink
	rm -Rf 0fc203298923f1d7c225cc6f43918d6663809e38.zip
- Get SBG SDK :
	wget "https://www.ensta-bretagne.fr/lebars/Share/SBG%20Systems.zip"
	unzip "SBG Systems.zip"
	cd "SBG Systems/Inertial SDK/Software Development/sbgECom/projects/unix"
- Add `set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")` option in `CMakeLists.txt` (e.g. in the `if (NOT MSVC)` condition) and build and install in `/usr/local/include` and  `/usr/local/lib` (or in `..`) :
	cmake .
	make
	sudo mkdir -p /usr/local/include/sbgECom
	sudo mkdir -p /usr/local/lib
	sudo mv ../../src/ /usr/local/include/sbgECom/src
	sudo mv ../../common/ /usr/local/include/sbgECom/common
	sudo mv ../../bin/libsbgECom.a /usr/local/lib/libsbgECom.a
	cd ../../../../../..
	rm -Rf "SBG Systems"
	rm -Rf "SBG Systems.zip"
- Get, build, install RPLIDAR SDK : https://github.com/lebarsfa/rplidar_sdk
- Follow `../ReadMe.txt`
