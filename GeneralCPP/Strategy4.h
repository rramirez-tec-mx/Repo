#pragma once
#include "IStrategy.h"

class DLL_EXPORT Strategy4 : public IStrategy
{
public:
	Strategy4(void);
	~Strategy4(void);

public:
	void DoAction(float a, float b, float& ret);
};

