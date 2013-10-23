#pragma once
#include <qos2.h>
#include "QoSExport.h"

class QOS2_EXPORTS_API CQoS2Manager
{
public:
	CQoS2Manager(void);
	~CQoS2Manager(void);

	void CreateHandle(HANDLE & QoSHandle);
	void CloseHandle(HANDLE & QoSHandle);	
};

