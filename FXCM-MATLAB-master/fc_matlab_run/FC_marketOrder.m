fc_msg = 0;

if not(libisloaded('fc_matlab'))
    display('need login first');
else
    [fc_msg] = calllib('fc_matlab','createMarketOrder', '01549059', 6000, 'S', 'GTC', 'EUR/USD', '');
end;    
%display(fc_msg);
%{
Parameters for createEntryOrder function:
accountNumber, trade size, side, TIF, symbol, ticket# 

accountNumber - account can be found in Trading Station
trade size - for FX min. 1000 or account min. trade size
side - B=Buy, S=Sell
Time in Force parameters: GTC, IOC, FOK 
symbol - any symbol available in your account
ticket# - it is the open position ticket number, can be found in Trading
            Station in Open positions tab

to close an open position the side should be oposite than open position,
the account should not be FIFO.
%}