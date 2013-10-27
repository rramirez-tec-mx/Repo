#pragma once
#include "GeneralCPPExport.h"

class GENERALCPP_EXPORTS_API Singleton
{
private:
	static bool instanceFlag;
	static Singleton *single;
	Singleton()
	{	
	}
public:
	static Singleton* getInstance();	
	static void DestroyInstance();
	~Singleton()
	{
		instanceFlag = false;
	}
};

