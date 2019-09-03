//------------------------------
// to compile this program use at prompt:
// mex -v fc_mexCallback.c fc_matlab.lib
//
// to change the default Visual Studio C++ compiler:
//mex -setup:C:\Programs\Matlab\R2015b\bin\win64\mexopts\msvcpp2015.xml C++
// to run it: fc_mexCallback
//------------------------------


#include "mex.h"
#include "matrix.h"
#include "fc_matlab.h"

// Callback function
void fc_mexCallback(char *msg, double msgType)
{
    static int count=0;
    
    if (count < 20)
    {
        for (count=0; count < 20; count++)
            mexPrintf("");
    }
    mexPrintf("%s", msg);
    //int k = (int)msgType;
    //mxArray *lhs[2]; 
    //mxArray *array_ptr;
    //array_ptr = mxCreateCellMatrix(1, 1, mxString);

    //lhs[0] =  mxCreateCellMatrix(1,1);
    
    //lhs[0] = mxCreateString(msg);
    //input_buf = mxArrayToString(lhs[0]);
    
    //mexEvalString(lhs[0]);
    //mexPrintf("mexPrintf: %s, %d\n", lhs[0], k); 
    
    //if (mxIsEmpty(lhs[0]) == false)
        
    
    /*
    //call Matlab function to print fcDLL messages from server
    switch(k)
    {
        case 1: mexCallMATLAB(0, NULL, 1, &lhs, "fc_pringMsgSystem");
                break;
        case 2: mexCallMATLAB(0, NULL, 1, &lhs, "fc_pringMsgTradingReports");
                break;
        case 3: mexCallMATLAB(0, NULL, 1, &lhs, "fc_pringMsgPrices");
                break;
    }
    */
}
// MEX Gateway
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //pointer to callback function
    void (*cbPtr)() = NULL;
    cbPtr = fc_mexCallback;
    //logout_fc();
    Register_Callback(cbPtr);
}
