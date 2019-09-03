%pring waiting orders to file or on the screen
fc_msg = 0;

if not(libisloaded('fc_matlab'))
    display('need login first');
else
    [fc_msg] = calllib('fc_matlab','printOrders', '01549059', 'waitingOrders.csv');
end;    

%{
Parameters for printOrders function:
accountNumber, fileName 

accountNumber - account can be found in Trading Station
fileName - output file name in CSV format, if fileNmae is blank the output
will be on the screen

example output:

OrderID,TradeID,ContingentOrderID,PrimaryID,Status,Amount,BuySell,Price
283991340, 117983846, , , W, 1000, S, 115.29300
284026505, 117996881, , , W, 1000, B, 1.40088

%}