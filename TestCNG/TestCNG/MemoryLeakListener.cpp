#include "MemoryLeakListener.h"


CMemoryLeakListener::CMemoryLeakListener(void)
{
}


CMemoryLeakListener::~CMemoryLeakListener(void)
{
}

void CMemoryLeakListener::OnTestStart(const ::testing::TestInfo& test_info)
{
	_CrtMemCheckpoint( &memAtStart );
}
void CMemoryLeakListener::OnTestEnd(const ::testing::TestInfo& test_info)
{
	if(test_info.result()->Passed())
	{
		CheckForMemLeaks(test_info); 
	}
}

void CMemoryLeakListener::CheckForMemLeaks(const ::testing::TestInfo& test_info)
{
    _CrtMemState memAtEnd;memAtEnd;
    _CrtMemCheckpoint( &memAtEnd );
    _CrtMemState memDiff;memDiff;
    if ( _CrtMemDifference( &memDiff, &memAtStart, &memAtEnd))
	{
        _CrtMemDumpStatistics( &memDiff );
		_CrtMemDumpAllObjectsSince(&memAtStart);
        FAIL() << "Memory leak in " << test_info.test_case_name() << "." << test_info.name() << '\n';
	}
}


int __cdecl printToStdErr(int reportType, char* szMsg, int* retVal){
 std::cerr << szMsg; 
 return 1; // No further processing required by _CrtDebugReport
}


void CMemoryLeakListener::OnTestProgramStart(const ::testing::UnitTest& unit_test)
{
	_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL, &printToStdErr);
}
void CMemoryLeakListener::OnTestProgramEnd(const ::testing::UnitTest& unit_test)
{
	_CrtSetReportHook2(_CRT_RPTHOOK_REMOVE, &printToStdErr);
}