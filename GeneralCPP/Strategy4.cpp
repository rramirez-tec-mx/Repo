#include "Strategy4.h"


Strategy4::Strategy4(void)
{
}


Strategy4::~Strategy4(void)
{
}

void Strategy4::DoAction(float a, float b ,float& ret)
{
	if(b!=0)
		ret = a / b;
	else 
		ret = 0;
}