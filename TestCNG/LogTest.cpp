#include "LogTest.h"
#include "..\Log\LogPrint.h"
using namespace std;
LogTest::LogTest()
{
}


LogTest::~LogTest()
{
}

TEST_F(LogTest, testPrint)
{
	char * stringMessage = "test di %s vale %d";
	string out = LogPrint::OutMessage(stringMessage, true, "ciao", 4);

	ASSERT_STREQ("test di ciao vale 4", out.c_str());
}