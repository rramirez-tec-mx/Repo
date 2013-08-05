#pragma once
#include "ExampleInheritanceBase.h"

#define DLL_EXPORT __declspec(dllexport)

class DLL_EXPORT ExampleInheritanceDerivedOne : public ExampleInheritanceBase
{
public:
	ExampleInheritanceDerivedOne(void);
	~ExampleInheritanceDerivedOne(void);

	void CalcRangeNumbers(int& outPar1, int proposedPar1) const;
};

