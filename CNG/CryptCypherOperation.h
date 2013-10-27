#pragma once
#include <string>
#include <memory>
#include <vector>
#include "CNGApi.h"

class CNG_EXPORTS_API CryptCypherOperation
{
public:
	CryptCypherOperation(void);
	~CryptCypherOperation(void);

	std::vector<unsigned char> EncryptData(const std::wstring & cryptAlgType, const int lenPlainText, unsigned char* plainText, unsigned long & lenCypherText, const std::wstring & passPhrase);
	std::vector<unsigned char> DecryptData(const std::wstring & cryptAlgType, const int lenCypherText, unsigned char *cypherText, const std::wstring & passPhrase);
private:
	void * GenerateSimmetricKeyFromPassPhrase(const std::wstring & cryptAlgTypeForSecret, int digestLength, const std::wstring & passPhrase, const std::wstring & cryptAlgTypeForEncryption);		   
};

