#pragma once
#include <windows.h>
#include "Ncrypt.h"
#include "CNGApi.h"
#include <vector>
#include <string>
//MS_KEY_STORAGE_PROVIDER         L"Microsoft Software Key Storage Provider"
//MS_SMART_CARD_KEY_STORAGE_PROVIDER L"Microsoft Smart Card Key Storage Provider"
//MS_PLATFORM_KEY_STORAGE_PROVIDER   L"Microsoft Platform Crypto Provider"

class CNG_EXPORTS_API CKeyStorageManager
{
public:
	CKeyStorageManager(void);
	~CKeyStorageManager(void);

	void EnumStorageProvider(std::vector<std::wstring> & listOfProvider);
	NCRYPT_PROV_HANDLE OpenStorageProvider(const std::wstring & providerName);
	void CreatePersistedKey(NCRYPT_PROV_HANDLE hProvider, NCRYPT_KEY_HANDLE *phKey, const std::wstring & pszAlgId, const std::wstring & pszKeyName, DWORD dwLegacyKeySpec, DWORD dwFlags);
	void FinalizePersistedKey(NCRYPT_KEY_HANDLE hKey);
	void OpenExistingPersistedKey(NCRYPT_PROV_HANDLE hProvider, NCRYPT_KEY_HANDLE *phKey, const std::wstring & pszKeyName, DWORD dwLegacyKeySpec, DWORD dwFlags);
	void DeleteExistingPersistedKey(NCRYPT_KEY_HANDLE hKey, DWORD dwFlags);	
};

