ret1 = 0;

if not(libisloaded('fc_matlab'))
    display('need login first');
else
    [ret1] = calllib('fc_matlab', 'getHistoryPrices', 'EUR/USD', 'H1',  '11.24.2015 15:00:00', '11.26.2015 15:00:00', 'priceLog1.csv');
end;    

%{
get historical price for any time period
parameters for getHistoryPrices function:
symbol, timeframe, timeFrom, timeTo, outputFile
timeFrame can be: t1=tick data, m1=1min, m5, m15, m30, H1=1 hour, H4, D1=daily, W1=weekly, M1=monthly data
output file - output file will be in CSV format
%}
