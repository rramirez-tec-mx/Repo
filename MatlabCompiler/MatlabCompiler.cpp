#include "MatlabCompiler.h"
#include "SimpleScript.h"
#include "mclmcr.h"
#include "matrix.h"
#include "MatlabCompiler2.h"

CMatlabCompiler::CMatlabCompiler(void)
{
	if (! mclInitializeApplication(NULL, 1))
	{
			MessageBox(HWND_DESKTOP,"Fucking MCR not loaded!!","Error",MB_OK);
			exit(-1);  
	}
}

CMatlabCompiler::~CMatlabCompiler(void)
{
}

double CMatlabCompiler::Do(double ingresso)
{
		
	if (!SimpleScriptInitialize())
	{
		MessageBox(HWND_DESKTOP,"Fucking dll not loaded!!","Error",MB_OK);
		return -1;  
	}

	mxArray* out = NULL;
	mxArray* in;
	int nargout = 1;

	in = mxCreateDoubleMatrix(1,1,mxREAL);
			
	memcpy(mxGetPr(in),&ingresso, 1*sizeof(double));

	mlfSimpleScript(nargout, &out, in);

	double *data = new double [1];	
	
	memcpy(data,mxGetPr(out), 1*sizeof(double));

	SimpleScriptTerminate();
	
	mxDestroyArray(in);
	double ret = data[0];
	delete[] data;

	return ret;
}

void CMatlabCompiler::CheckType()
{
	
	if (!MatlabCompiler2Initialize())
	{
		MessageBox(HWND_DESKTOP,"Fucking dll not loaded!!","Error",MB_OK);
		exit(-1);  
	}


			
}


