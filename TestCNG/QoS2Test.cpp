#include "QoS2Test.h"


CQoS2Test::CQoS2Test(void)
{
}


CQoS2Test::~CQoS2Test(void)
{
}

//con 10000 tentativi e 2 byte, RNG_ALGORITHM e RNG_FIPS186_DSA_ALGORITHM impiegano lo stesso tempo
//RNG_DUAL_EC_ALGORITHM invece impiega più di 100 volte di più :-/
TEST_F(CQoS2Test, MaanageQoSHandle) 
{
	CQoS2Manager manager;
	HANDLE QoSHandle = nullptr;
	manager.CreateHandle(QoSHandle);
	ASSERT_NE(QoSHandle, nullptr);	
	manager.CloseHandle(QoSHandle);
	ASSERT_EQ(QoSHandle, nullptr);
}