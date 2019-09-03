%get real time prices
ret1 = 0;

if not(libisloaded('fc_matlab'))
    display('need login first');
else
    [ret1] = calllib('fc_matlab','getRealTimePrices','EUR/USD');
end;    
%display(ret1);

% function getRealTimePrices parameter: symbol
% to stop real time prices run FC_pricesStop.m
