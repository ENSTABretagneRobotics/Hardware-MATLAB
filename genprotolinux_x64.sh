/opt/matlab/R2020b/bin/matlab -nodisplay -nosplash -nodesktop -wait -r "try, run('./hardwarex_setup.m'), catch me, fprintf('%s / %s\n', me.identifier, me.message), end, exit"
mv -f hardwarex_proto.m linux_x64/
mv -f hardwarex_thunk_glnxa64.so linux_x64/
rm -Rf hardwarex.i hardwarex_thunk_glnxa64.c hardwarex_thunk_glnxa64.obj hardwarex_thunk_glnxa64.a hardwarex_thunk_glnxa64.exp
