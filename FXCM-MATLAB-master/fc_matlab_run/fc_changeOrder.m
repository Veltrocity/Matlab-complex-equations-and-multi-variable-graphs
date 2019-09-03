fc_msg = 0;

if not(libisloaded('fc_matlab'))
    display('need login first');
else
    [fc_msg] = calllib('fc_matlab','changeOrder', '01537581', '330244057', 1.1133, 20000);
end;    

%{
Parameters for changeELSstopLimit function:
accountNumber, trade ID, limiPrice, stopPrice

accountNumber - account can be found in Trading Station
Order ID - waiting Order ID
limitPrice - new  price, 0 = no change
amount - new amount, 0 = no change 

%}