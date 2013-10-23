#pragma once
#include "gtest.h"
#include "..\..\CNG\CryptRandomNumberGenerator.h"
#include "Common.h"
class RNGTest: public ::testing::Test 
{
public:
	RNGTest(void);
	~RNGTest(void);
protected:
	CryptRandomNumberGenerator m_cryptRandomNumberGenerator;
};

