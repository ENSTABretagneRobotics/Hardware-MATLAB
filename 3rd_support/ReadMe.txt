MAVLink, SBG, RPLIDAR SDK support
===============

Try first prebuilt versions from https://github.com/ENSTABretagneRobotics/Hardware-MATLAB/releases. Otherwise, try to use CMake (and uncomment `#define ENABLE_MAVLINK_SUPPORT`, `#define ENABLE_SBG_SDK_SUPPORT`, `#define ENABLE_RPLIDAR_SDK_SUPPORT` in `hardwarex.h`) or check what follows if needed to rebuild.

Windows: 
- In `hardwarex.h`, uncomment `#define ENABLE_MAVLINK_SUPPORT`, `#define ENABLE_SBG_SDK_SUPPORT`, `#define ENABLE_RPLIDAR_SDK_SUPPORT`.
- Copy the headers from https://github.com/mavlink/c_library_v1/archive/a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip in `C:\Program Files (x86)\MAVLinkSDK\mavlink` for a 64 bit version of Windows or `C:\Program Files\MAVLinkSDK\mavlink` for a 32 bit version of Windows (or in `..\MAVLinkSDK\mavlink`).
- Copy the files from https://www.ensta-bretagne.fr/lebars/Share/SBG%20Systems.zip and https://github.com/lebarsfa/rplidar_sdk/tree/enstabre (rebuild this one using Visual Studio 2010 or later or get a prebuilt version for Visual Studio 2017 from https://github.com/lebarsfa/rplidar_sdk/releases/latest/download/rplidar_sdk.zip or a previous version from https://github.com/lebarsfa/rplidar_sdk/releases (note that some hardware versions might require a specific version of rplidar_sdk.zip)) in `C:\Program Files (x86)` for a 64 bit version of Windows or `C:\Program Files` for a 32 bit version of Windows (or in `..`).
- Rebuild using Visual Studio 2012 or later and put the resulting hardwarex.dll in the corresponding `..\x86` and `..\x64` folders.
- In MATLAB, run `mex -setup` and `mex -setup C++` and choose Visual Studio 2013 or later.
- Run `hardwarex_setup.m` and put the resulting `hardwarex_proto.m` and `hardwarex_thunk_pcwin64.dll` in the corresponding `..\x86` and `..\x64` folders.
- Optional: If you have the `sed` command, you can try to correct some warnings/errors in `hardwarex_proto.m` by checking patchproto.bat...
- Follow `..\ReadMe.txt`

Linux/macOS: 
- In `hardwarex.h`, uncomment `#define ENABLE_MAVLINK_SUPPORT`, `#define ENABLE_SBG_SDK_SUPPORT`, `#define ENABLE_RPLIDAR_SDK_SUPPORT`.
- In the `Makefile`, check that `LDFLAGS += -lsbgECom -lsl_lidar_sdk` is uncommented.
- For macOS, you might want to install Homebrew and wget: 
	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
	brew install wget
- Copy the headers from https://github.com/mavlink/c_library_v1/archive/a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip in `/usr/local/include/mavlink` (or `../MAVLinkSDK/mavlink`):
	wget https://github.com/mavlink/c_library_v1/archive/a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip
	unzip a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip
	sudo mkdir -p /usr/local/include
	sudo mv -f c_library_v1-a44ece42bc76b1f257f4f540d7283e0c874ac6d9/ /usr/local/include/mavlink
	rm -Rf a44ece42bc76b1f257f4f540d7283e0c874ac6d9.zip
- Get SBG SDK:
	wget "https://www.ensta-bretagne.fr/lebars/Share/SBG%20Systems.zip"
	unzip -q -o "SBG Systems.zip"
	cd "SBG Systems/Inertial SDK/Software Development/sbgECom/projects/unix"
- If needed, add `set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")` in `CMakeLists.txt` (e.g. in the `if (NOT MSVC)` condition) and build and install in `/usr/local/include` and  `/usr/local/lib` (or in `..`):
	cmake .
	make
	sudo mkdir -p /usr/local/include/sbgECom
	sudo mkdir -p /usr/local/lib
	sudo cp -Rf ../../src/ /usr/local/include/sbgECom/src
	sudo cp -Rf ../../common/ /usr/local/include/sbgECom/common
	sudo cp -Rf ../../bin/libsbgECom.a /usr/local/lib/libsbgECom.a
	cd ../../../../../..
	rm -Rf "SBG Systems" "SBG Systems.zip"
- Get, build, install RPLIDAR SDK: 
	wget https://github.com/lebarsfa/rplidar_sdk/archive/refs/heads/enstabre.zip --no-check-certificate -nv
	unzip -q -o enstabre.zip
	cd rplidar_sdk-enstabre
	rm -Rf output
	# On macOS, you might need to run something similar to
	#export SDKROOT=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk
	make
	sudo rm -Rf /usr/local/include/rplidar_sdk
	sudo mkdir -p /usr/local/include/rplidar_sdk/sdk
	sudo mkdir -p /usr/local/lib
	sudo mkdir -p /usr/local/bin
	sudo cp -Rf sdk/include /usr/local/include/rplidar_sdk/sdk/
	sudo cp -Rf sdk/src /usr/local/include/rplidar_sdk/sdk/
	# On macOS, replace Linux with Darwin
	sudo cp -Rf output/Linux/Release/libsl_lidar_sdk.a /usr/local/lib/libsl_lidar_sdk.a
	sudo cp -Rf output/Linux/Release/ultra_simple /usr/local/bin/ultra_simple
	sudo cp -Rf output/Linux/Release/simple_grabber /usr/local/bin/simple_grabber
	sudo cp -Rf output/Linux/Release/custom_baudrate /usr/local/bin/custom_baudrate
	cd ..
	rm -Rf rplidar_sdk-enstabre enstabre.zip
- Follow `../ReadMe.txt`
