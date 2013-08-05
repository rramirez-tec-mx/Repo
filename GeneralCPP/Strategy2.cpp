#include "Strategy2.h"


Strategy2::Strategy2(void)
{
}


Strategy2::~Strategy2(void)
{
}

void Strategy2::DoAction(float a, float b ,float& ret)
{
	ret = a - b;
}