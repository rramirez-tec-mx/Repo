#pragma once
#include <sal.h>
#include "GeneralCPPExport.h"

class GENERALCPP_EXPORTS_API SalStuff
{
public:
	SalStuff();
	~SalStuff();


};

_Check_return_ bool func();

GENERALCPP_EXPORTS_API  _Check_return_ int testRetValue(_In_ int& t);

bool testRetValue1(bool b);


