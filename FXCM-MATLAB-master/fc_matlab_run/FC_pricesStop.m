%stop real time prices
ret1 = 0;

if not(libisloaded('fc_matlab'))
    display('need login first');
else
    [ret1] = calllib('fc_matlab','stopPrices','none');
end;    

% Stop real time prices 
