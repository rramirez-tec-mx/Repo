#pragma once
#include "IStrategy.h"

class DLL_EXPORT Strategy1 : public IStrategy
{
public:
	Strategy1(void);
	~Strategy1(void);

public:
	void DoAction(float a, float b, float& ret);
};

