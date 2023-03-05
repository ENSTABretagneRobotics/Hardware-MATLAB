"/Applications/MATLAB_R2020b.app/bin/matlab" -nodisplay -nosplash -nodesktop -wait -r "try, run('./hardwarex_setup.m'), catch me, fprintf('%s / %s\n', me.identifier, me.message), end, exit"
mv -f hardwarex_proto.m mac/
mv -f hardwarex_thunk_maci64.dylib mac/
rm -Rf hardwarex.i hardwarex_thunk_maci64.c hardwarex_thunk_maci64.obj hardwarex_thunk_maci64.a hardwarex_thunk_maci64.exp
