#pragma once
#include "LogApi.h"
#include <windows.h>

class LOG_EXPORTS_API LogOutputDebugString
{
public:
	static void LogMessage(char * message, DWORD lastError, SECURITY_STATUS retValue);
};

