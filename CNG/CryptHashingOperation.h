#pragma once
#include <string>
#include <memory>
#include <vector>
#include "CNGApi.h"

class CNG_EXPORTS_API CCryptHashingOperation
{
public:
	CCryptHashingOperation(void);
	~CCryptHashingOperation(void);

public:	
	std::wstring CalcHashInHexForm(std::wstring messageToHash, std::wstring hashAlgType, int digestLength);
	std::vector<unsigned char> CalcRawHash(std::wstring messageToHash, std::wstring hashAlgType);

private:
	std::vector<unsigned char> ConvertWStringToArrayOfByte(std::wstring stringToConvert);
	std::vector<unsigned char> CreateHash(std::wstring messageToHash, std::wstring hashAlgType);

};

