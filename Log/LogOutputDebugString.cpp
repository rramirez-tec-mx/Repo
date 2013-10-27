#include "LogOutputDebugString.h"
#include <Windows.h>
#include <stdio.h>
#include <string>

using namespace std;

void LogOutputDebugString::LogMessage(string && message, DWORD lastError, SECURITY_STATUS retValue)
{
	char  msgbuf[300];	
	message = message + " LastError = %ld , SecurityStatus = 0x%x \n";
	sprintf_s(msgbuf, message.c_str(), lastError, retValue);
	OutputDebugStringA(msgbuf);
}