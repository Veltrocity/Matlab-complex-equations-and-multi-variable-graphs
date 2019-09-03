ret2=0;
if (libisloaded('fc_matlab'))
    [ret2] = calllib('fc_matlab', 'logout_fc');
    
    unloadlibrary fc_matlab
end;

