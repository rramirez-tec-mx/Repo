#include "HashingTest.h"
#include <windows.h>
#include <iostream>

#include "..\..\GeneralCPP\Timer.h"


using namespace std;

CHashingTest::CHashingTest(void): m_messageToHash(L"abb")
{
	
}


CHashingTest::~CHashingTest(void)
{
}

TEST_F(CHashingTest, CalculateMD5Hash) 
{		
	PUCHAR resultHash = NULL;
	wstring hashAlgType = BCRYPT_MD5_ALGORITHM;
	int digestLength = 16;	
	wstring hashHex;
	hashHex = m_cryptHashOperation.CalcHashInHexForm(m_messageToHash, hashAlgType, digestLength);	
	ASSERT_EQ(hashHex,L"ea01e5fd8e4d8832825acdd20eac5104");
	
}


TEST_F(CHashingTest, CalculateSHA1Hash) 
{		
	PUCHAR resultHash = NULL;
	wstring hashAlgType = BCRYPT_SHA1_ALGORITHM;
	int digestLength = 20;
	wstring hashHex;

	CTimer theTimer;
	theTimer.Start();
	hashHex = m_cryptHashOperation.CalcHashInHexForm(m_messageToHash, hashAlgType, digestLength);
	theTimer.Stop();
	
	ASSERT_EQ(hashHex,L"c64d3fcde20c5cd03142171e5ac47a87aa3c8ace");
}


TEST_F(CHashingTest, CalculateSHA256Hash) 
{		
	PUCHAR resultHash = NULL;
	wstring hashAlgType = BCRYPT_SHA256_ALGORITHM;
	int digestLength = 32;
	wstring hashHex;

	CTimer theTimer;
	theTimer.Start();
	hashHex = m_cryptHashOperation.CalcHashInHexForm(m_messageToHash, hashAlgType, digestLength);
	theTimer.Stop();

	ASSERT_EQ(hashHex,L"715edf8ba8729420cd4d1ce85ed61954a9f531f8c548df728c407effe839296d");									                  								   
}


TEST_F(CHashingTest, CalculateSHA384Hash) 
{		
	PUCHAR resultHash = NULL;
	wstring hashAlgType = BCRYPT_SHA384_ALGORITHM;
	int digestLength = 48;
	wstring hashHex;

	CTimer theTimer;
	theTimer.Start();
	hashHex = m_cryptHashOperation.CalcHashInHexForm(m_messageToHash, hashAlgType, digestLength);
	theTimer.Stop();

	ASSERT_EQ(hashHex,L"b3a671398773967b17dfac229541179c1dc47289bc666aa0cf63fb746e2e9af4f3835f689ab1cad580ddaa6167a2c1fd");
}

TEST_F(CHashingTest, CalculateSHA512Hash) 
{		
	PUCHAR resultHash = NULL;
	wstring hashAlgType = BCRYPT_SHA512_ALGORITHM;
	int digestLength = 64;
	wstring hashHex;

	CTimer theTimer;
	theTimer.Start();
	hashHex = m_cryptHashOperation.CalcHashInHexForm(m_messageToHash, hashAlgType, digestLength);
	theTimer.Stop();

	ASSERT_EQ(hashHex,L"198ec4853b4fa11a26a55c9d6ac1d06e6af9401772906c4313a0d39b31891ad07860379d699c28f3840ec26b1f3e1ce33448e095496b6299ffe8fc090d71fff6");
}