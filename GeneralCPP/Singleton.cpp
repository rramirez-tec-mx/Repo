#include "Singleton.h"


bool Singleton::instanceFlag = false;
Singleton* Singleton::single = nullptr;

Singleton* Singleton::getInstance()
{
	if (!instanceFlag)
	{
		single = new Singleton();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

void Singleton::DestroyInstance()
{
	if (single)
	{
		delete single;
		single = nullptr;
	}	
}

