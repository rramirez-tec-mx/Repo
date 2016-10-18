#pragma once
#include <Windows.h>
#include "GeneralCPPExport.h"
#include "versionhelpers.h"
#include <map>
class GENERALCPP_EXPORTS_API WindowsVersion
{
public:
	WindowsVersion();
	~WindowsVersion();
	std::map<size_t, bool> FillMapOfWindowsVersion();
	
	enum WinVersion { WINXP_OR_GREATER = 0, 
							  WINXP_SP1_OR_GREATER = 1,
							  WINXP_SP2_OR_GREATER = 2,
							  WINXP_SP3_OR_GREATER = 3,
							  WINVISTA_OR_GREATER = 4,
							  WINVISTA_SP1_OR_GREATER = 5,
							  WINVISTA_SP2_OR_GREATER = 6,
							  WINSEVEN_OR_GREATER = 7,
							  WINSEVEN_SP1_OR_GREATER = 8,
							  WINEIGHT_OR_GREATER = 9,
							  WINEIGHT_POINT1_OR_GREATER = 10,
							  WIN_SERVER = 11
							};


};

