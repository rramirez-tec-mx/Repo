#include "ExampleInheritanceBase.h"


ExampleInheritanceBase::ExampleInheritanceBase(void)
{
}


ExampleInheritanceBase::~ExampleInheritanceBase(void)
{
}

void ExampleInheritanceBase::CalcRangeNumbers(int& outPar1, int proposedPar1) const
{
	outPar1 = proposedPar1;
}