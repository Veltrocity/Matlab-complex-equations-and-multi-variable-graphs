fc_msg = 0;

if not(libisloaded('fc_matlab'))
    display('need login first');
else
    [fc_msg] = calllib('fc_matlab','changeELSstopLimit', '01537581', '142090851', 86.445, 86.112);
end;    

%{
Parameters for changeELSstopLimit function:
accountNumber, trade ID, limiPrice, stopPrice

accountNumber - account can be found in Trading Station
trade ID - ELS trade ID
limitPrice - new limit price, 0 if no change requeires 
stopPrice - new stop price, 0 if no change requeires 

%}