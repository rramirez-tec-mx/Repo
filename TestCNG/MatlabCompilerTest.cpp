#include "MatlabCompilerTest.h"
#include "..\..\MatlabCompiler\MatlabCompiler.h"

using namespace std;


CMatlabCompilerTest::CMatlabCompilerTest(void)
{
}


CMatlabCompilerTest::~CMatlabCompilerTest(void)
{
}

TEST_F(CMatlabCompilerTest, DISABLED_TestSimpleScript) 
{			
	CMatlabCompiler matlabCompiler;
	
	double val = 6;

	ASSERT_EQ(10*val,matlabCompiler.Do(val));
}

TEST_F(CMatlabCompilerTest, DISABLED_TestMatlabCompiler2) 
{			
	CMatlabCompiler matlabCompiler;
		
	matlabCompiler.CheckType();
}
