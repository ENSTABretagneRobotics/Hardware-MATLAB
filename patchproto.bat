@cd /d "%~dp0"

@sed -i 's/FcnPtr/voidPtr/g' x86\hardwarex_proto.m
@sed -i 's/FcnPtr/voidPtr/g' x64\hardwarex_proto.m

@sed -i 's/s_LIST_ENTRYPtr/voidPtr/g' x86\hardwarex_proto.m
@sed -i 's/s_LIST_ENTRYPtr/voidPtr/g' x64\hardwarex_proto.m

@sed -i 's/\x27 int (\* _Nullable _close )( void \*)\x27, \x27error1\x27, \x27 int (\* _Nullable _read ) ( void \*, char \*, int )\x27, \x27error2\x27, \x27voidPtr\x27, \x27error3\x27, \x27 int (\* _Nullable _write )( void \*, const char \*, int )\x27/\x27int32Ptr\x27, \x27error1\x27, \x27int32Ptr\x27, \x27error2\x27, \x27voidPtr\x27, \x27error3\x27, \x27int32Ptr\x27/g' mac\hardwarex_proto.m

@sed -i 's/\x27reserved0\x27, \x27uint8\x232\x27, \x27flags\x27, \x27error\x27/\x27reserved0\x27, \x27uint8\x232\x27, \x27flags\x27, \x27uint8\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27reserved0\x27, \x27uint8\x232\x27, \x27flags\x27, \x27error\x27/\x27reserved0\x27, \x27uint8\x232\x27, \x27flags\x27, \x27uint8\x27/g' x64\hardwarex_proto.m
@sed -i 's/\x27reserved0\x27, \x27uint8\x232\x27, \x27flags\x27, \x27error\x27/\x27reserved0\x27, \x27uint8\x232\x27, \x27flags\x27, \x27uint8\x27/g' mac\hardwarex_proto.m
@sed -i 's/\x27reserved0\x27, \x27uint8\x232\x27, \x27flags\x27, \x27error\x27/\x27reserved0\x27, \x27uint8\x232\x27, \x27flags\x27, \x27uint8\x27/g' linux_x64\hardwarex_proto.m

@sed -i 's/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27error\x27/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27uint8\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27error\x27/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27uint8\x27/g' x64\hardwarex_proto.m
@sed -i 's/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27error\x27/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27uint8\x27/g' mac\hardwarex_proto.m
@sed -i 's/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27error\x27/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27uint8\x27/g' linux_x64\hardwarex_proto.m

@sed -i 's/\x27reserved2\x27, \x27uint8\x234\x27, \x27flags\x27, \x27error\x27/\x27reserved2\x27, \x27uint8\x234\x27, \x27flags\x27, \x27uint32\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27reserved2\x27, \x27uint8\x234\x27, \x27flags\x27, \x27error\x27/\x27reserved2\x27, \x27uint8\x234\x27, \x27flags\x27, \x27uint32\x27/g' x64\hardwarex_proto.m
@sed -i 's/\x27reserved2\x27, \x27uint8\x234\x27, \x27flags\x27, \x27error\x27/\x27reserved2\x27, \x27uint8\x234\x27, \x27flags\x27, \x27uint32\x27/g' mac\hardwarex_proto.m
@sed -i 's/\x27reserved2\x27, \x27uint8\x234\x27, \x27flags\x27, \x27error\x27/\x27reserved2\x27, \x27uint8\x234\x27, \x27flags\x27, \x27uint32\x27/g' linux_x64\hardwarex_proto.m

@sed -i 's/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27/g' x64\hardwarex_proto.m
@sed -i 's/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27/g' mac\hardwarex_proto.m
@sed -i 's/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27/g' linux_x64\hardwarex_proto.m

@sed -i 's/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' x64\hardwarex_proto.m
@sed -i 's/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' mac\hardwarex_proto.m
@sed -i 's/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' linux_x64\hardwarex_proto.m

@sed -i 's/\x27fixStat\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixStat\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27fixStat\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixStat\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' x64\hardwarex_proto.m
@sed -i 's/\x27fixStat\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixStat\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' mac\hardwarex_proto.m
@sed -i 's/\x27fixStat\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixStat\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' linux_x64\hardwarex_proto.m
