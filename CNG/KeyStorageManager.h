#pragma once
#include <windows.h>
#include "Ncrypt.h"
#include <vector>

#define DLL_EXPORT __declspec(dllexport)

//MS_KEY_STORAGE_PROVIDER         L"Microsoft Software Key Storage Provider"
//MS_SMART_CARD_KEY_STORAGE_PROVIDER L"Microsoft Smart Card Key Storage Provider"
//MS_PLATFORM_KEY_STORAGE_PROVIDER   L"Microsoft Platform Crypto Provider"

class DLL_EXPORT CKeyStorageManager
{
public:
	CKeyStorageManager(void);
	~CKeyStorageManager(void);

	void EnumStorageProvider(std::vector<std::wstring> & listOfProvider);
	NCRYPT_PROV_HANDLE OpenStorageProvider(std::wstring providerName);
};

