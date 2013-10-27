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
	std::wstring CalcHashInHexForm(const std::wstring & messageToHash, const std::wstring & hashAlgType, int digestLength);
	std::vector<unsigned char> CalcRawHash(const std::wstring & messageToHash, const std::wstring & hashAlgType);

private:
	std::vector<unsigned char> ConvertWStringToArrayOfByte(const std::wstring & stringToConvert);
	std::vector<unsigned char> CreateHash(const std::wstring & messageToHash, const std::wstring & hashAlgType);

};

