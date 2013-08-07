#pragma once
#include <qos2.h>
#define DLL_EXPORT __declspec(dllexport)

class DLL_EXPORT CQoS2Manager
{
public:
	CQoS2Manager(void);
	~CQoS2Manager(void);

	void CreateHandle(HANDLE & QoSHandle);
	void CloseHandle(HANDLE & QoSHandle);	
};

