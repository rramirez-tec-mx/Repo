#pragma once
#include "LogApi.h"
#include <windows.h>
#include <string>
class LOG_EXPORTS_API LogOutputDebugString
{
public:
	static void LogMessage(std::string && message, DWORD lastError, SECURITY_STATUS retValue);
};

