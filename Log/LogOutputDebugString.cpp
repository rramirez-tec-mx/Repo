#include "LogOutputDebugString.h"
#include <Windows.h>
#include <stdio.h>
#include <string>

using namespace std;

void LogOutputDebugString::LogMessage(char * message, DWORD lastError, SECURITY_STATUS retValue)
{
	char  msgbuf[300];
	string msg = message;
	msg = msg + " LastError = %ld , SecurityStatus = 0x%x \n";
	sprintf_s(msgbuf, msg.c_str(), lastError, retValue);
	OutputDebugStringA(msgbuf);
}