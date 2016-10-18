#include "QoS2Manager.h"
#include <string>
#include <iostream>

using namespace std;

CQoS2Manager::CQoS2Manager(void)
{
}


CQoS2Manager::~CQoS2Manager(void)
{
}

void CQoS2Manager::CreateHandle(HANDLE & QoSHandle)
{
	BOOL QoSResult;
	QOS_VERSION Version;	
	Version.MajorVersion = 1;
	Version.MinorVersion = 0;
	QoSResult = QOSCreateHandle(&Version, &QoSHandle);
	
	if (QoSResult != TRUE)
	{
		char  msgbuf[200];
		sprintf_s(msgbuf, "QOSCreateHandle failed. Error: %ld\n", GetLastError());
		OutputDebugStringA(msgbuf);

	}
}

void CQoS2Manager::CloseHandle(HANDLE & QoSHandle)
{
	if (QoSHandle != NULL)
	{
		if( QOSCloseHandle(QoSHandle) != TRUE)
		{
			char  msgbuf[200];
			sprintf_s(msgbuf, "QOSCloseHandle failed. Error: %ld\n", GetLastError());
			OutputDebugStringA(msgbuf);
		}
		else
			QoSHandle = NULL;
	}
}