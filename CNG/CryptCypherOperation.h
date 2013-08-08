#pragma once
#include <string>
#include <memory>
#include "CNGApi.h"

class DLL_EXPORT CryptCypherOperation
{
public:
	CryptCypherOperation(void);
	~CryptCypherOperation(void);

	std::vector<unsigned char> EncryptData(std::wstring cryptAlgType, const int lenPlainText, unsigned char* plainText, unsigned long & lenCypherText, std::wstring passPhrase);
	std::vector<unsigned char> DecryptData(std::wstring cryptAlgType, const int lenCypherText, unsigned char *cypherText, std::wstring passPhrase);
private:
	void * GenerateSimmetricKeyFromPassPhrase(std::wstring cryptAlgTypeForSecret, int digestLength, std::wstring passPhrase, std::wstring cryptAlgTypeForEncryption);
};

