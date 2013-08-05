#include "StdAfx.h"
#include "CryptCypherOperation.h"
#include "CryptHashingOperation.h"
#include <string>

using namespace std;

CryptCypherOperation::CryptCypherOperation(void)
{
	
}


CryptCypherOperation::~CryptCypherOperation(void)
{
	
}


vector<BYTE> CryptCypherOperation::EncryptData(wstring cryptAlgType, const int lenPlainText, BYTE *plainText, ULONG & lenCypherText, wstring passPhrase)
{
	NTSTATUS ret;	
	BCRYPT_KEY_HANDLE hKey = NULL;	

	hKey = GenerateSimmetricKeyFromPassPhrase(BCRYPT_MD5_ALGORITHM, 16, passPhrase, cryptAlgType.c_str());

	ret = BCryptEncrypt(hKey, plainText, lenPlainText, NULL, NULL, 0, NULL, 0, &lenCypherText, BCRYPT_BLOCK_PADDING);
		
	vector<BYTE> cypherText;
	cypherText.resize(lenCypherText);
	DWORD cbData = 0;
	ret = BCryptEncrypt(hKey, plainText, lenPlainText, NULL, NULL, 0, &cypherText[0], lenCypherText, &cbData, BCRYPT_BLOCK_PADDING);
	
	ret = BCryptDestroyKey(hKey);
	
	return cypherText;
}

vector<BYTE> CryptCypherOperation::DecryptData(wstring cryptAlgType, const int lenCypherText, BYTE *cypherText, wstring passPhrase)
{
	NTSTATUS ret;
	BCRYPT_KEY_HANDLE hKey = NULL;
	ULONG lenPlainText;
	
	hKey = GenerateSimmetricKeyFromPassPhrase(BCRYPT_MD5_ALGORITHM, 16, passPhrase, cryptAlgType.c_str());
	ret = BCryptDecrypt(hKey, cypherText, lenCypherText, NULL, NULL, 0, NULL, 0, &lenPlainText, BCRYPT_BLOCK_PADDING);

	vector<BYTE> decypherText;	
	decypherText.resize(lenPlainText+1);
	ret = BCryptDecrypt(hKey, cypherText, lenCypherText, NULL, NULL, 0, &decypherText[0], lenPlainText, &lenPlainText, BCRYPT_BLOCK_PADDING);
	decypherText[lenCypherText] = 0x00;

	ret = BCryptDestroyKey(hKey);

	return decypherText;
}

BCRYPT_KEY_HANDLE CryptCypherOperation::GenerateSimmetricKeyFromPassPhrase(wstring cryptAlgTypeForSecret, int digestLength, wstring passPhrase, wstring cryptAlgTypeForEncryption)
{
	NTSTATUS ret;	
	BCRYPT_ALG_HANDLE hAlgorithm;	
	ULONG cbSecret = 0;	
	PUCHAR pbKeyObject = NULL;
	ULONG cbKeyObject = 0;	
	CCryptHashingOperation hashingOperation;
	BCRYPT_KEY_HANDLE hKey = NULL;
	
	vector<BYTE> pbSecret;
	pbSecret = hashingOperation.CalcRawHash(passPhrase, cryptAlgTypeForSecret, digestLength);
	cbSecret = digestLength;

	ret = BCryptOpenAlgorithmProvider(&hAlgorithm, cryptAlgTypeForEncryption.c_str(), NULL, 0);
	ret = BCryptGenerateSymmetricKey(hAlgorithm, &hKey, pbKeyObject, cbKeyObject, &pbSecret[0], cbSecret, 0);

	if(hAlgorithm)
	{
		BCryptCloseAlgorithmProvider(hAlgorithm, 0);
	}

	return hKey;
}