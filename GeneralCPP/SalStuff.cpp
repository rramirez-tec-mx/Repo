#include "SalStuff.h"
#include <stdio.h>
#include <direct.h>
//#include <codeanalysis\warnings.h>

//#pragma warning (default:6031)


SalStuff::SalStuff()
{
}


SalStuff::~SalStuff()
{
}


_Check_return_ bool func()
{
	return true;
}

_Check_return_ int func_range(_In_range_(1, 3) int val)
{
	return val * 2;
}

class P
{
public:
	int a;
	int b;
};

void f()
{	
	//func(); //  Warning C6031
	//int *p = new int[10];
	//delete p; //  Warning C6283

	//P *p = nullptr;	
	//p->a = 1;  Warning C6011

	//{
	//	int aa;
	//	aa = 1; aa;

	//	{
	//		int aa;  Warning C6246
	//		aa = 2; aa;
	//	}
	//}
	//int aa; int val=4;
	//if (func_range(val) > 1)
	//	aa = 1;
}



GENERALCPP_EXPORTS_API  _Check_return_ int testRetValue(_In_ int& t)
{	 
	t = 1;
	return 1;
}