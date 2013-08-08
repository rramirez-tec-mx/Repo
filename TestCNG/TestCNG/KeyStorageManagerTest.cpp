#include "KeyStorageManagerTest.h"
#include "..\..\CNG\KeyStorageManager.h"

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
//	if(provHandle)
	//	NCryptFreeObject(provHandle); //necessario farlo, per ora non lo faccio
}
