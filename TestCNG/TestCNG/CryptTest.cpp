#include "CryptTest.h"
#include <windows.h>
#include <iostream>
#include "..\..\GeneralCPP\Timer.h"

using namespace std;

CryptTest::CryptTest(void) : m_plainText("1234567")
{
	
}


CryptTest::~CryptTest(void)
{
}

TEST_F(CryptTest, CryptEncryptWithDESFromHashSecret) 
{
	
	PUCHAR resultHash = NULL;
	BYTE* encryptedRawBYTEData = NULL;	
	BYTE* decryptedRawBYTEData = NULL;
	wstring cryptAlgType = BCRYPT_DES_ALGORITHM;
	ULONG lenCypherText=0;
	wstring passPhrase = L"abbCCC";
		
	int sizePlainText = m_plainText.size();
	BYTE* plainTextRawBYTE = new BYTE[sizePlainText+1];
	
	for (int i=0; i<sizePlainText;i++)
	{
		plainTextRawBYTE[i] = m_plainText.at(i);
	}
	plainTextRawBYTE[sizePlainText] = 0x00;	
			
	encryptedRawBYTEData = m_cryptCypherOperation.EncryptData(cryptAlgType, sizePlainText, plainTextRawBYTE, lenCypherText, passPhrase);
	
	decryptedRawBYTEData = m_cryptCypherOperation.DecryptData(cryptAlgType, lenCypherText, encryptedRawBYTEData, passPhrase);
		
	for(int i=0;i<sizePlainText;i++)
	{
		ASSERT_EQ(decryptedRawBYTEData[i],m_plainText.at(i));
	}
	
	if(NULL != encryptedRawBYTEData)
	{
		delete[] encryptedRawBYTEData;
		encryptedRawBYTEData = NULL;
	}

	
	if(NULL != decryptedRawBYTEData)
	{
		delete[] decryptedRawBYTEData;
		decryptedRawBYTEData = NULL;
	}

	
	
	if(NULL != plainTextRawBYTE)
	{
		delete[] plainTextRawBYTE;
		plainTextRawBYTE = NULL;
	}
	
}
