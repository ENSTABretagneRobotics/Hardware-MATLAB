@cd /d "%~dp0"

@"%ProgramFiles(x86)%\MATLAB\R2015b\bin\matlab.exe" -nodisplay -nosplash -nodesktop -wait -r "try, run('%~dp0hardwarex_setup.m'), catch me, fprintf('%s / %s\n', me.identifier, me.message), end"
@move /Y "hardwarex_proto.m" "x86"\
@del /f /q hardwarex.i
