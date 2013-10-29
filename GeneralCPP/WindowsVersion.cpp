#include "WindowsVersion.h"
#include <Windows.h>
#include <map>

using namespace std;

WindowsVersion::WindowsVersion()
{
}


WindowsVersion::~WindowsVersion()
{
}

map<size_t, bool> WindowsVersion::FillMapOfWindowsVersion()
{
	map<size_t, bool> mapOfCondition;

	mapOfCondition[WinVersion::WINXP_OR_GREATER] = IsWindowsXPOrGreater();
	mapOfCondition[WinVersion::WINXP_SP1_OR_GREATER] = IsWindowsXPSP1OrGreater();
	mapOfCondition[WinVersion::WINXP_SP2_OR_GREATER] = IsWindowsXPSP2OrGreater();
	mapOfCondition[WinVersion::WINXP_SP3_OR_GREATER] = IsWindowsXPSP3OrGreater();
	mapOfCondition[WinVersion::WINVISTA_OR_GREATER] = IsWindowsVistaOrGreater();
	mapOfCondition[WinVersion::WINVISTA_SP1_OR_GREATER] = IsWindowsVistaSP1OrGreater();
	mapOfCondition[WinVersion::WINVISTA_SP2_OR_GREATER] = IsWindowsVistaSP2OrGreater();
	mapOfCondition[WinVersion::WINSEVEN_OR_GREATER] = IsWindows7OrGreater();
	mapOfCondition[WinVersion::WINSEVEN_SP1_OR_GREATER] = IsWindows7SP1OrGreater();
	mapOfCondition[WinVersion::WINEIGHT_OR_GREATER] = IsWindows8OrGreater();
	mapOfCondition[WinVersion::WINEIGHT_POINT1_OR_GREATER] = IsWindows8Point1OrGreater();
	mapOfCondition[WinVersion::WIN_SERVER] = IsWindowsServer();
	
	return mapOfCondition;
}