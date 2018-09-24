cd /d "%~dp0"

set HARDWARE_PYTHON_PATH=%~d0\devel\GitHub\Hardware-Python

copy /B /Y /Z "Release\hardwarex.dll" %HARDWARE_PYTHON_PATH%\x86\hardwarex.dll"
copy /B /Y /Z "x64\Release\hardwarex.dll" %HARDWARE_PYTHON_PATH%\x64\hardwarex.dll"

copy /B /Y /Z "Release\hardwarex.dll" %HARDWARE_PYTHON_PATH%\hardwarex.dll"

pause
