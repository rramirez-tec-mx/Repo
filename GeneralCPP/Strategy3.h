#pragma once
#include "IStrategy.h"

class DLL_EXPORT Strategy3 : public IStrategy
{
public:
	Strategy3(void);
	~Strategy3(void);

public:
	void DoAction(float a, float b, float& ret);
};

