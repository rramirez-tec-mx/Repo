#include "SSLTest.h"
#include <windows.h>
#include <bcrypt.h>
#pragma warning(disable:4389)
using namespace std;

SSLTest::SSLTest(void)
{
}


SSLTest::~SSLTest(void)
{
}

TEST_F(SSLTest, test_SSLEnumCipherSuite)
{
	SSL ssl;
	vector<wstring> sslInfoCipherSuite, sslInfoCipher;
	ssl.EnumCipherSuite(sslInfoCipherSuite, sslInfoCipher);

	for (size_t k=0; k<sslInfoCipherSuite.size(); k++)
	{		
		wcout << "Ciphersuite supported " << sslInfoCipherSuite[k] << endl;
	}
}
TEST_F(SSLTest, test_SSLEnumProtocolProviders)
{
	SSL ssl;
	DWORD pdwProviderCount;			
	NCryptProviderName *ppProviderList = nullptr;
	ssl.EnumProtocolProviders(pdwProviderCount, &ppProviderList);

	ASSERT_EQ(pdwProviderCount, 1);
	wstring name = ppProviderList->pszName;
	ASSERT_STREQ(name.c_str(), L"Microsoft SSL Protocol Provider");
}
