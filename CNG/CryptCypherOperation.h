#pragma once
#include <windows.h>
#include <string>
#include <memory>
#include <vector>
#define DLL_EXPORT __declspec(dllexport)

class DLL_EXPORT CryptCypherOperation
{
public:
	CryptCypherOperation(void);
	~CryptCypherOperation(void);

	std::vector<BYTE> EncryptData(std::wstring cryptAlgType, const int lenPlainText, BYTE* plainText, ULONG & lenCypherText, std::wstring passPhrase);
	std::vector<BYTE> DecryptData(std::wstring cryptAlgType, const int lenCypherText, BYTE *cypherText, std::wstring passPhrase);
private:
	BCRYPT_KEY_HANDLE GenerateSimmetricKeyFromPassPhrase(std::wstring cryptAlgTypeForSecret, int digestLength, std::wstring passPhrase, std::wstring cryptAlgTypeForEncryption);
};

