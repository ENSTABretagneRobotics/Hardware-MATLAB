function [result] = GPSInputMAVLinkDevice(pMAVLinkDevice, gps_lat, gps_lon, gps_alt, yaw)
result = calllib('hardwarex', 'GPSInputMAVLinkDevicex', pMAVLinkDevice, gps_lat, gps_lon, gps_alt, yaw);
