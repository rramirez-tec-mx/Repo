#pragma once
#include "gtest\gtest.h"
#include "Common.h"


class CKeyStorageManagerTest: public ::testing::Test 
{
public:
	CKeyStorageManagerTest(void);
	~CKeyStorageManagerTest(void);

protected:
	std::wstring m_pszKeyName;

};

