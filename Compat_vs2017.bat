@cd /d "%~dp0"

@md "%TMP%\hardwarex"

@set /P DISABLE_MAVLINK="Disable MAVLink (0, 1) : "
@set /P DISABLE_SBG="Disable SBG (0, 1) : "
@set /P ENABLE_XP="Enable XP Platform Toolset (0, 1) : "
@echo.

@if "%DISABLE_MAVLINK%"=="1" (

@echo Disabling MAVLink 

@replaceinfile /infile hardwarex.h /outfile "%TMP%\hardwarex\hardwarex.h" /searchstr "#define ENABLE_MAVLINK_SUPPORT" /replacestr "//#define ENABLE_MAVLINK_SUPPORT"
@copy /Y /B "%TMP%\hardwarex\hardwarex.h" hardwarex.h

@rem replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";ENABLE_MAVLINK_SUPPORT" /replacestr ""
@rem copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";MAVLinkSDK;$(ProgramFiles)\MAVLinkSDK" /replacestr ""
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr "<ClInclude Include=""Hardware\MAVLinkDevice.h"" />" /replacestr "<ClInclude Include=""Hardware\MAVLinkDevice.h""><ExcludedFromBuild Condition=""'$(Configuration)|$(Platform)'=='Debug|Win32'"">true</ExcludedFromBuild><ExcludedFromBuild Condition=""'$(Configuration)|$(Platform)'=='Release|Win32'"">true</ExcludedFromBuild></ClInclude>"
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj
)

@if "%DISABLE_SBG%"=="1" (

@echo Disabling SBG 

@replaceinfile /infile hardwarex.h /outfile "%TMP%\hardwarex\hardwarex.h" /searchstr "#define ENABLE_SBG_SUPPORT" /replacestr "//#define ENABLE_SBG_SUPPORT"
@copy /Y /B "%TMP%\hardwarex\hardwarex.h" hardwarex.h

@rem replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";ENABLE_SBG_SUPPORT" /replacestr ""
@rem copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";SBG Systems\Inertial SDK\Software Development\sbgECom\src;SBG Systems\Inertial SDK\Software Development\sbgECom\common;$(ProgramFiles)\SBG Systems\Inertial SDK\Software Development\sbgECom\src;$(ProgramFiles)\SBG Systems\Inertial SDK\Software Development\sbgECom\common" /replacestr ""
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";SBG Systems\Inertial SDK\Software Development\sbgECom\x86\vc15\lib;$(ProgramFiles)\SBG Systems\Inertial SDK\Software Development\sbgECom\x86\vc15\lib" /replacestr ""
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";SBG Systems\Inertial SDK\Software Development\sbgECom\x86\vc15\staticlib;$(ProgramFiles)\SBG Systems\Inertial SDK\Software Development\sbgECom\x86\vc15\staticlib" /replacestr ""
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";SBG Systems\Inertial SDK\Software Development\sbgECom\x64\vc15\lib;$(ProgramFiles)\SBG Systems\Inertial SDK\Software Development\sbgECom\x64\vc15\lib" /replacestr ""
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";SBG Systems\Inertial SDK\Software Development\sbgECom\x64\vc15\staticlib;$(ProgramFiles)\SBG Systems\Inertial SDK\Software Development\sbgECom\x64\vc15\staticlib" /replacestr ""
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";sbgEComd.lib" /replacestr ""
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr ";sbgECom.lib" /replacestr ""
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr "<ClInclude Include=""Hardware\SBG.h"" />" /replacestr "<ClInclude Include=""Hardware\SBG.h""><ExcludedFromBuild Condition=""'$(Configuration)|$(Platform)'=='Debug|Win32'"">true</ExcludedFromBuild><ExcludedFromBuild Condition=""'$(Configuration)|$(Platform)'=='Release|Win32'"">true</ExcludedFromBuild></ClInclude>"
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj
)

@if "%ENABLE_XP%"=="1" (

@echo Enabling XP Platform Toolset

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr "<PlatformToolset>v141</PlatformToolset>" /replacestr "<PlatformToolset>v141_xp</PlatformToolset>"
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj
)

@if "%ENABLE_XP%"=="0" (

@echo Disabling XP Platform Toolset

@replaceinfile /infile hardwarex.vcxproj /outfile "%TMP%\hardwarex\hardwarex.vcxproj" /searchstr "<PlatformToolset>v141_xp</PlatformToolset>" /replacestr "<PlatformToolset>v141</PlatformToolset>"
@copy /Y /B "%TMP%\hardwarex\hardwarex.vcxproj" hardwarex.vcxproj
)

@echo.

@pause

@rd /s /q "%TMP%\hardwarex"

@exit
