@cd /d "%~dp0"

@rem genprotox86.bat with exit
@"%ProgramFiles(x86)%\MATLAB\R2015b\bin\matlab.exe" -nodisplay -nosplash -nodesktop -wait -r "try, run('%~dp0hardwarex_setup.m'), catch me, fprintf('%s / %s\n', me.identifier, me.message), end, exit"
@move /Y "hardwarex_proto.m" "x86"\
@del /f /q hardwarex.i

@rem genprotox64.bat with exit
@"%ProgramFiles%\MATLAB\R2022b\bin\matlab.exe" -nodisplay -nosplash -nodesktop -wait -r "try, run('%~dp0hardwarex_setup.m'), catch me, fprintf('%s / %s\n', me.identifier, me.message), end, exit"
@move /Y "hardwarex_proto.m" "x64"\
@move /Y "hardwarex_thunk_pcwin64.dll" "x64"\
@del /f /q hardwarex.i hardwarex_thunk_pcwin64.c hardwarex_thunk_pcwin64.obj hardwarex_thunk_pcwin64.lib hardwarex_thunk_pcwin64.exp
