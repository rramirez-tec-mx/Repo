#include "KeyStorageManagerTest.h"
#include "..\..\CNG\KeyStorageManager.h"
#include "..\..\CNG\CryptRandomNumberGenerator.h"

using namespace std;

CKeyStorageManagerTest::CKeyStorageManagerTest(void)
{
}


CKeyStorageManagerTest::~CKeyStorageManagerTest(void)
{
}

TEST_F(CKeyStorageManagerTest, EnumerateStorageProviderTest) 
{
	CKeyStorageManager manager;
	vector<wstring> listOfProvider;
	manager.EnumStorageProvider(listOfProvider);

	ASSERT_EQ(listOfProvider[0], MS_KEY_STORAGE_PROVIDER);
	ASSERT_EQ(listOfProvider[1], MS_PLATFORM_KEY_STORAGE_PROVIDER);
	ASSERT_EQ(listOfProvider[2], MS_SMART_CARD_KEY_STORAGE_PROVIDER);
}

TEST_F(CKeyStorageManagerTest, OpenStorageProviderTest) 
{
	CKeyStorageManager manager;
	NCRYPT_PROV_HANDLE provHandle;
	provHandle = manager.OpenStorageProvider(MS_KEY_STORAGE_PROVIDER);	
	ASSERT_NE(provHandle, (NCRYPT_PROV_HANDLE)nullptr);
	//if(provHandle)
	//	NCryptFreeObject(provHandle); //necessario farlo, per ora non lo faccio
}

TEST_F(CKeyStorageManagerTest, CreatePeristedKeyTest) 
{
	CKeyStorageManager manager;
	NCRYPT_PROV_HANDLE provHandle = NULL;
	NCRYPT_KEY_HANDLE  hKey       = NULL;
	wstring pszAlgId = BCRYPT_AES_ALGORITHM;
	wstring pszKeyName = L"TestCNG_AES_KEY";
	DWORD dwLegacyKeySpec = 0;
	DWORD dwFlags = 0;

	provHandle = manager.OpenStorageProvider(MS_KEY_STORAGE_PROVIDER);
	manager.CreatePersistedKey(provHandle, &hKey, pszAlgId, pszKeyName, dwLegacyKeySpec, dwFlags);
	ASSERT_NE(hKey, (NCRYPT_KEY_HANDLE)nullptr);	
}

TEST_F(CKeyStorageManagerTest, CreateAndFinalizeAndOpenAndDeletePeristedKeyTest) 
{
	CKeyStorageManager manager;	
	NCRYPT_KEY_HANDLE  hKey       = NULL;
	NCRYPT_PROV_HANDLE provHandle;
	wstring pszAlgId = BCRYPT_AES_ALGORITHM;
	
	DWORD dwLegacyKeySpec = 0;
	DWORD dwFlags = 0;

	m_pszKeyName = CryptRandomNumberGenerator().Generate(BCRYPT_RNG_ALGORITHM, 10);
	
	provHandle = manager.OpenStorageProvider(MS_KEY_STORAGE_PROVIDER);
	ASSERT_NE(provHandle, (NCRYPT_PROV_HANDLE)nullptr);
	manager.CreatePersistedKey(provHandle, &hKey, pszAlgId, m_pszKeyName, dwLegacyKeySpec, dwFlags);
	ASSERT_NE(hKey, (NCRYPT_KEY_HANDLE)nullptr);
	manager.FinalizePersistedKey(hKey);
	Sleep(3000);
	manager.OpenExistingPersistedKey(provHandle, &hKey, pszAlgId, m_pszKeyName, dwLegacyKeySpec, dwFlags);
	ASSERT_NE(hKey, (NCRYPT_KEY_HANDLE)nullptr);

	manager.DeleteExistingPersistedKey(hKey, dwFlags);
}

