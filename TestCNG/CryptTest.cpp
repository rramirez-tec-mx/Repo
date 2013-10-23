#include "CryptTest.h"
#include <windows.h>
#include <iostream>
#include "..\GeneralCPP\Timer.h"

using namespace std;

CryptTest::CryptTest(void) : m_plainText("1234567")
{
	
}


CryptTest::~CryptTest(void)
{
}

TEST_F(CryptTest, CryptEncryptWithDESFromHashSecret) 
{
	
	vector<BYTE> encryptedRawBYTEData;	
	vector<BYTE> decryptedRawBYTEData;
	wstring cryptAlgType = BCRYPT_DES_ALGORITHM;
	ULONG lenCypherText=0;
	wstring passPhrase = L"abbCCC";
		
	size_t sizePlainText = m_plainText.size();
	vector<BYTE> plainTextRawBYTE;
	plainTextRawBYTE.resize(sizePlainText+1);
	
	for (size_t i=0; i<sizePlainText;i++)
	{
		plainTextRawBYTE[i] = m_plainText.at(i);
	}
	plainTextRawBYTE[sizePlainText] = 0x00;	
			
	encryptedRawBYTEData = m_cryptCypherOperation.EncryptData(cryptAlgType, sizePlainText, &plainTextRawBYTE[0], lenCypherText, passPhrase);
	
	decryptedRawBYTEData = m_cryptCypherOperation.DecryptData(cryptAlgType, lenCypherText, &encryptedRawBYTEData[0], passPhrase);
		
	for(size_t i=0;i<sizePlainText;i++)
	{
		ASSERT_EQ(decryptedRawBYTEData[i],m_plainText.at(i));
	}				
}
