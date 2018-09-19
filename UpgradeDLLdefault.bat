cd /d "%~dp0"

copy /B /Y /Z "Release\hardwarex.dll" .\default\x86\hardwarex.dll"
copy /B /Y /Z "x64\Release\hardwarex.dll" .\default\x64\hardwarex.dll"
copy /B /Y /Z "hardwarex.so" .\default\linux_x64\hardwarex.so"

pause
