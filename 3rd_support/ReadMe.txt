MAVLink, SBG, RPLIDAR SDK support (if needed to rebuild)
===============
Windows : 
- In `hardwarex.h`, check that `#define ENABLE_MAVLINK_SUPPORT`, `#define ENABLE_SBG_SDK_SUPPORT`, `#define ENABLE_RPLIDAR_SDK_SUPPORT` are uncommented.
- Copy the headers from https://github.com/mavlink/c_library_v1/archive/a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip in `C:\Program Files (x86)\MAVLinkSDK\mavlink` for a 64 bit version of Windows or `C:\Program Files\MAVLinkSDK\mavlink` for a 32 bit version of Windows (or in `..\MAVLinkSDK\mavlink`).
- Copy the files from https://www.ensta-bretagne.fr/lebars/Share/SBG%20Systems.zip and https://github.com/lebarsfa/rplidar_sdk (rebuild this one using Visual Studio 2010 or later or get a prebuilt version for Visual Studio 2017 on https://www.ensta-bretagne.fr/lebars/Share/rplidar_sdk.zip) in `C:\Program Files (x86)` for a 64 bit version of Windows or `C:\Program Files` for a 32 bit version of Windows (or in `..`).
- Rebuild using Visual Studio 2012 or later and put the resulting hardwarex.dll in the corresponding `..\x86` and `..\x64` folders.
- In MATLAB, run `mex -setup` and `mex -setup C++` and choose Visual Studio 2013 or later.
- Run `hardwarex_setup.m` and put the resulting `hardwarex_proto.m` and `hardwarex_thunk_pcwin64.dll` in the corresponding `..\x86` and `..\x64` folders.
- Optional : If you have the `sed` command, you can try to correct some warnings/errors in `hardwarex_proto.m` by checking patchproto.bat...
- Follow `..\ReadMe.txt`

Linux/macOS : 
- In `hardwarex.h`, check that `#define ENABLE_MAVLINK_SUPPORT`, `#define ENABLE_SBG_SDK_SUPPORT`, `#define ENABLE_RPLIDAR_SDK_SUPPORT` are uncommented.
- In the `Makefile`, check that `LDFLAGS += -lsbgECom -lrplidar_sdk` is uncommented.
- For macOS, you might want to install Homebrew and wget : 
	/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	brew install wget
- Copy the headers from https://github.com/mavlink/c_library_v1/archive/a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip in `/usr/local/include/mavlink` (or `../MAVLinkSDK/mavlink`) :
	wget https://github.com/mavlink/c_library_v1/archive/a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip
	unzip a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip
	sudo mkdir -p /usr/local/include
	sudo mv -f c_library_v1-a44ece42bc76b1f257f4f540d7283e0c874ac6d9/ /usr/local/include/mavlink
	rm -Rf a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip
- Get SBG SDK :
	wget "https://www.ensta-bretagne.fr/lebars/Share/SBG%20Systems.zip"
	unzip -q -o "SBG Systems.zip"
	cd "SBG Systems/Inertial SDK/Software Development/sbgECom/projects/unix"
- If needed, add `set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")` in `CMakeLists.txt` (e.g. in the `if (NOT MSVC)` condition) and build and install in `/usr/local/include` and  `/usr/local/lib` (or in `..`) :
	cmake .
	make
	sudo mkdir -p /usr/local/include/sbgECom
	sudo mkdir -p /usr/local/lib
	sudo mv -f ../../src/ /usr/local/include/sbgECom/src
	sudo mv -f ../../common/ /usr/local/include/sbgECom/common
	sudo mv -f ../../bin/libsbgECom.a /usr/local/lib/libsbgECom.a
	cd ../../../../../..
	rm -Rf "SBG Systems" "SBG Systems.zip"
- Get, build, install RPLIDAR SDK : 
	wget https://www.ensta-bretagne.fr/lebars/Share/rplidar_sdk.zip
	unzip -q -o rplidar_sdk.zip
	cd rplidar_sdk/sdk
	# On macOS, you might need to run somthing similar to
	#export SDKROOT=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk
	make
	sudo mkdir -p /usr/local/include/rplidar_sdk/sdk/sdk
	sudo mkdir -p /usr/local/lib
	sudo mkdir -p /usr/local/bin
	sudo mv -f sdk/include /usr/local/include/rplidar_sdk/sdk/sdk/
	sudo mv -f sdk/src /usr/local/include/rplidar_sdk/sdk/sdk/
	sudo mv -f output/Linux/Release/librplidar_sdk.a /usr/local/lib/librplidar_sdk.a
	sudo mv -f output/Linux/Release/ultra_simple /usr/local/bin/ultra_simple
	sudo mv -f output/Linux/Release/simple_grabber /usr/local/bin/simple_grabber
	cd ../..
	rm -Rf rplidar_sdk rplidar_sdk.zip
- Follow `../ReadMe.txt`
