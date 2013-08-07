#pragma once
#include <windows.h>
#include "Ncrypt.h"
#include <vector>

#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CKeyStorageManager
{
public:
	CKeyStorageManager(void);
	~CKeyStorageManager(void);

	void EnumStorageProvider(std::vector<std::wstring> & listOfProvider);
};

