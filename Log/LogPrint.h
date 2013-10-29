#pragma once
#include "LogApi.h"
#include <string>
class LOG_EXPORTS_API LogPrint
{
public:	
	static std::string OutMessage(char* msg, bool display, ...);
};

