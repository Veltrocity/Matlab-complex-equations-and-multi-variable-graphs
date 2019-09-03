Using Forex Connect API with Matlab

The fc_matlab.dll allows to connect to FXCM server and get real time and historical prices, 
place market, limit, stop and ELS orders.
All functions used by ForexConnect are asynchronous, so the fc_matlab.dll implements an event-driven 
architecture it receives messages/events from FXCM server and pass them to fc_mexCallback function,
from there it get passed to Matlab functions.
To start the FC API first open the FC_login.m, select Run, select Change Folder so the fc_matlab_run 
is the current Matlab folder.
To login you need FXCM Demo or Real account, to get a demo account it can be done from fxcm.com.

the currect DLL works only with Matlab 64 bit 
the project build with Visual Studio 2015

The fc_mexCallback.c was compiled with Matlab R2015b, if you are using earlier version you may need to re-compile fc_mexCallback.c, 
to compile it: mex -v fc_mexCallback.c fc_matlab.lib

The DLL source code is included fc_matlab folder, the fc_matlab_run folder includes all files to run the fc_matlab.dll and the Matlab code

The fc_matlab.dll is using Forex Connect API in C++, below are links about FC API,
Our official web about API
https://www.fxcm.com/services/api-trading/
FXCM Forex Connect API - downloads for different platforms
http://www.fxcodebase.com/wiki/index.php/Download
Choosing proper SDK:
http://fxcodebase.com/wiki/index.php/Choosing_Proper_SDK

online FC help:  http://www.fxcorporate.com/help/CPlusPlus/
FC API forum:  http://www.dailyfxforum.com/forums/1163-ForexConnect




if you don't have VS 2015 installed please download the Visual C++ Redistributable for Visual Studio 2015
https://www.microsoft.com/en-us/download/details.aspx?id=48145

For any FXCM API question please email to api@fxcm.com

