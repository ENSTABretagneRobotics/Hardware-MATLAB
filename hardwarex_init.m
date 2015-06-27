% Ideally, you should call :
% hardwarex_init
% in the beginning (otherwise the initialization will be done when necessary but might take several seconds), and :
% unloadlibrary('hardwarex');
% at the end (this will not be done automatically, unloadlibrary might fail if all the variables that use types from the library are not removed using clean...).
if not(libisloaded('hardwarex'))
    switch (computer)
        case 'PCWIN64'
            loadlibrary('hardwarex', @hardwarex_proto);
            %libfunctions hardwarex -full
        otherwise
            loadlibrary('hardwarex');
            %libfunctions hardwarex -full
    end
end
