#include "LogPrint.h"
#include <stdio.h>
#include <stdarg.h>

using namespace std;

string LogPrint::OutMessage(char* formatString, bool display, ...)
{
	char buffer[15];
	va_list args;
	va_start(args, display);	
	_vsnprintf_s(buffer, _countof(buffer), _TRUNCATE, formatString, args);
	perror(buffer);
	va_end(args);
	return buffer;
}