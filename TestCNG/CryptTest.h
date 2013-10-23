#pragma once
#include "gtest.h"
#include "..\..\CNG\CryptCypherOperation.h"
#include "Common.h"
class CryptTest: public ::testing::Test 
{
public:
	CryptTest(void);
	~CryptTest(void);
protected:
	
	CryptCypherOperation m_cryptCypherOperation;
	std::string m_plainText;
};

