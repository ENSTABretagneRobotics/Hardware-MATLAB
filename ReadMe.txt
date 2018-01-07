Hardware-MATLAB
===============
Windows : 
- In MATLAB, go to File\Set Path...\Add Folder... and add this folder as well as x86 folder if you use MATLAB 32 bit or x64 folder if you use MATLAB 64 bit.
- Check test_XXX.m files for usage information.

Linux/Mac : 
- Follow the instructions in the Makefile.

Sample : http://www.ensta-bretagne.fr/lebars/Share/buggy_real_gps.zip for the buggy based on an Android smartphone described on http://www.ensta-bretagne.fr/lebars/buggy_android_full.pdf .

Change the device path and other parameters in the configuration files if necessary. Mind the line endings in the configuration files depending on the OS (use e.g. the command dos2unix *.txt to convert line endings for Linux)!

Tested on Windows 10 64 bit using MATLAB R2016a.

Hardware support : 
- Hokuyo : Hokuyo URG-04LX-UG01 laser telemeter.
- Maestro : Pololu Mini Maestro 6, 18, 24 servo controllers.
- MAVLinkDevice (not enabled by default, see mavlink_support folder) : ArduPilot/ArduFlyer/HKPilot Mega (APM 2.5), PX4FLOW.
- MT : Xsens MTi, MTi-G AHRS.
- NMEADevice : GPS, Furuno WS200 weather station.
- RazorAHRS : SparkFun 9DOF Razor IMU.
- RPLIDAR : RPLIDAR A2 laser telemeter.
- SSC-32 : Lynxmotion SSC-32, SSC-32u servo controllers.
- ublox : ublox GPS.

See also https://github.com/ENSTABretagneRobotics/Android, https://github.com/ENSTABretagneRobotics/Hardware-CPP, https://github.com/ENSTABretagneRobotics/Hardware-Python, https://github.com/ENSTABretagneRobotics/Hardware-Java.
