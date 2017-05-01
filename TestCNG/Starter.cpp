#include "Starter.h"
#include <tchar.h>
#include "gtest\gtest.h"
#include "MemoryLeakListener.h"

using namespace std;

void bye (void)
{
  puts ("Goodbye, cruel world....");
}
     
int _tmain(int argc, _TCHAR* argv[])
{	
	//::testing::InitGoogleTest(&argc, argv);   return RUN_ALL_TESTS(); 
	//exit(0);
		
	atexit(bye);
	 
    ::testing::InitGoogleTest(&argc, argv);

  //  auto &listeners = ::testing::UnitTest::GetInstance()->listeners();
	
	//listeners.Append(new CMemoryLeakListener{});

    int result = RUN_ALL_TESTS();
    return result;
}
