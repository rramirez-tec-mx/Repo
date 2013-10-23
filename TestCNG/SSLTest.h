#pragma once
#include "gtest\gtest.h"
#include "..\CNG\ssl.h"

class SSLTest: public ::testing::Test 
{
public:
	SSLTest(void);
	~SSLTest(void);
};

