#pragma once
#include <windows.h>
#include <string>
#include <memory>
#include <vector>

#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CCryptHashingOperation
{
public:
	CCryptHashingOperation(void);
	~CCryptHashingOperation(void);

public:	
	std::wstring CalcHashInHexForm(std::wstring messageToHash, std::wstring hashAlgType, int digestLength);
	std::vector<BYTE> CalcRawHash(std::wstring messageToHash, std::wstring hashAlgType, int digestLength);

private:
	std::vector<BYTE> ConvertWStringToArrayOfByte(std::wstring stringToConvert);
	std::vector<BYTE> CreateHash(std::wstring messageToHash, std::wstring hashAlgType);

};

