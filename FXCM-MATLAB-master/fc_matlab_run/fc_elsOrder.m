fc_msg = 0;

if not(libisloaded('fc_matlab'))
    display('need login first');
else
    [fc_msg] = calllib('fc_matlab','createELSorder', '01549059', 6000, 'B', 'EUR/USD', 'Range', 'GTC', 1.15996, 1.15999, 1.34, 1.1211, 10, '');
end;    

%{
Parameters for createEntryOrder function:
accountNumber, trade size, side, symbol, order type, TIF, price, limiPrice, stopPrice, trailing stop 

accountNumber - account can be found in Trading Station
trade size - for FX min. 1000 or account min. trade size
side - B=Buy, S=Sell
symbol - any symbol available in your account
order type - can be one of: Market, Stop, Limit, Range
TIF (Time in Force) parameters: GTC, IOC, FOK 
price - the open position price, if market order the price will be ignored
rangeMax - for range order
limitPrice - it's the profit, if main position is Buy then limitPrice should be above the market 
stopPrice - Stop Loss, should be below the market in case of long position
trailing stop - attached to stopPrice, the number is in pips, example for long position:
    current Ask price is 100, 
    Limit = 130
    Stop = 70
    when Bid = 110, the Stop will move to 80

for Range order (used to control the slippage):
    use the price as rangeMininum price
    for Buy order the price should be >= Ask, the rangeMax > Ask, for
    example if current Ask=100, price=102 and rangeMax=104, the order will
    be executed when Ask=102 and fill price will be 104 or better. 
%}