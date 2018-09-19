cd /d "%~dp0"

copy /B /Y /Z "Release\hardwarex.dll" .\mavlink_support\x86\hardwarex.dll"
copy /B /Y /Z "x64\Release\hardwarex.dll" .\mavlink_support\x64\hardwarex.dll"
copy /B /Y /Z "hardwarex.so" .\mavlink_support\linux_x64\hardwarex.so"

pause
