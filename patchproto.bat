@cd /d "%~dp0"

@sed -i 's/FcnPtr/voidPtr/g' x86\hardwarex_proto.m
@sed -i 's/FcnPtr/voidPtr/g' x64\hardwarex_proto.m
@sed -i 's/s_LIST_ENTRYPtr/voidPtr/g' x86\hardwarex_proto.m
@sed -i 's/s_LIST_ENTRYPtr/voidPtr/g' x64\hardwarex_proto.m
@sed -i 's/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27error\x27/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27uint8\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27error\x27/\x27sec\x27, \x27uint8\x27, \x27valid\x27, \x27uint8\x27/g' x64\hardwarex_proto.m
@sed -i 's/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27/\x27gpsFix\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27/g' x64\hardwarex_proto.m
@sed -i 's/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixType\x27, \x27uint8\x27, \x27flags\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' x64\hardwarex_proto.m
@sed -i 's/\x27fixStat\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixStat\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' x86\hardwarex_proto.m
@sed -i 's/\x27fixStat\x27, \x27error\x27, \x27flags2\x27, \x27error\x27/\x27fixStat\x27, \x27uint8\x27, \x27flags2\x27, \x27uint8\x27/g' x64\hardwarex_proto.m
