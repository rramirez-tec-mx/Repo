#pragma once
#include "gtest\gtest.h"
class CMemoryLeakListener : public ::testing::EmptyTestEventListener 
{
public:
	CMemoryLeakListener(void);
	~CMemoryLeakListener(void);

	 void OnTestStart(const ::testing::TestInfo& test_info);
	 void OnTestEnd(const ::testing::TestInfo& test_info);
	 void OnTestProgramStart(const ::testing::UnitTest& unit_test);
	 void OnTestProgramEnd(const ::testing::UnitTest& unit_test);

private:
	_CrtMemState memAtStart;	
	void CheckForMemLeaks(const ::testing::TestInfo& test_info);
};

