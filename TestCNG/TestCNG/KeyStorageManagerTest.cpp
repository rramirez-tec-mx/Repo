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

	ASSERT_EQ(listOfProvider[0], L"Microsoft Software Key Storage Provider");
	ASSERT_EQ(listOfProvider[1], L"Microsoft Platform Crypto Provider");
	ASSERT_EQ(listOfProvider[2], L"Microsoft Smart Card Key Storage Provider");
}