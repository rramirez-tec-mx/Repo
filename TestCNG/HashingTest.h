#pragma once
#include "gtest\gtest.h"
#include <string>
#include "..\CNG\CryptHashingOperation.h"

#include "Common.h"
class CHashingTest: public ::testing::Test 
{
public:
	CHashingTest(void);
	~CHashingTest(void);

public:
	void CalculateHash();
protected:
	std::wstring m_messageToHash;
	CCryptHashingOperation m_cryptHashOperation;
};

