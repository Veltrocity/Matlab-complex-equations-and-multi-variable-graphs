%init callback function
fc_mexCallback();

if not(libisloaded('fc_matlab'))
    [notfound, warnings] = loadlibrary('fc_matlab.dll', 'fc_matlab.h');
end;    

[notfound2, warnings2] = calllib('fc_matlab', 'login_fc', 'D101546502001', '55', 'Demo', 'http://fxcorporate.com/Hosts.jsp');
display('--- ignore warning messages ---');
%libfunctionsview fcDLL

%{
login_fc parameters:
username
password
connection - Demo or Real
URL - http://fxcorporate.com/Hosts.jsp
%}
