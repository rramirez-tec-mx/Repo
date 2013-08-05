#pragma once
#include "IStrategy.h"

class DLL_EXPORT Strategy2 : public IStrategy
{
public:
	Strategy2(void);
	~Strategy2(void);

public:
	void DoAction(float a, float b, float& ret);
};

