Hardware-MATLAB
===============
Windows : 
- Launch MATLAB preferably by right-clicking on `Run as administrator` on MATLAB shortcut (this is sometimes required to be able to access serial devices).
- Check `test_razorahrs.m`, `test_rplidar.m`, etc. files for usage information.

Linux/macOS : 
- Follow the instructions in the `Makefile`, note that a `CMakeLists.txt` is also provided for cmake.

Change the device path (e.g. `COM9`) and other parameters in the configuration files (`RazorAHRS0.txt`, `RPLIDAR0.txt`, etc.) if necessary. Mind the line endings in the configuration files depending on the OS (use e.g. the command `dos2unix *.txt` to convert line endings for Linux)! Ensure that you closed any other application that might use the devices (reboot if unsure). Note that you need to press the ESC key to exit cleanly the test script, if you interrupt the script by `CTRL+C`, MATLAB might crash or you might not be able to launch successfully again the test script...

Sample : http://www.ensta-bretagne.fr/lebars/Share/buggy_real_gps.zip for the buggy based on an Android smartphone described on http://www.ensta-bretagne.fr/lebars/buggy_android_full.pdf .

Tested on Windows 10 64 bit using MATLAB R2017b 64 bit and MATLAB R2015b 32 bit, Ubuntu 18.04 64 bit using MATLAB R2017b 64 bit.

Hardware support : 
- Hokuyo : Hokuyo URG-04LX-UG01 laser telemeter.
- IM483I : Intelligent Motion Systems IM483I step motor controller.
- MAVLinkDevice (see `3rd_support` folder if needed to rebuild) : ArduPilot/ArduFlyer/HKPilot Mega (APM 2.5), PX4FLOW.
- MDM : Tritech Micron Data Modem (or other kinds of simple RS232 modems).
- MT : Xsens MTi, MTi-G AHRS.
- NMEADevice (superseded by ublox) : GPS, Furuno WS200 weather station.
- P33x : Keller pressure sensor PAA-33x.
- Pololu : Pololu Mini Maestro 6, 18, 24 servo controllers, Pololu Jrk (preliminary support).
- RazorAHRS : SparkFun 9DOF Razor IMU (flash firmware from https://github.com/lebarsfa/razor-9dof-ahrs if needed).
- RPLIDAR (see `3rd_support` folder if needed to rebuild with RPLIDAR SDK) : RPLIDAR A1, A2, A3 laser telemeters.
- SBG (see `3rd_support` folder if needed to rebuild with SBG SDK) : SBG Systems Ellipse AHRS.
- SSC-32 : Lynxmotion SSC-32, SSC-32u servo controllers.
- ublox : ublox GPS (only with NMEA protocol), Furuno WS200 weather station, or other NMEA-compatible devices with supported NMEA sentences.

See also https://github.com/ENSTABretagneRobotics/Hardware-CPP , https://github.com/ENSTABretagneRobotics/Hardware-Python , https://github.com/ENSTABretagneRobotics/Hardware-Java , https://github.com/ENSTABretagneRobotics/Android .
