#include "SSLTest.h"

using namespace std;

SSLTest::SSLTest(void)
{
}


SSLTest::~SSLTest(void)
{
}

TEST_F(SSLTest, test1SSL)
{
	SSL ssl;
	vector<wstring> sslInfoCipherSuite, sslInfoCipher;
	ssl.EnumCipherSuite(sslInfoCipherSuite, sslInfoCipher);

	for (size_t k=0; k<sslInfoCipherSuite.size(); k++)
	{		
		wcout << "Ciphersuite supported " << sslInfoCipherSuite[k] << endl;
	}

}