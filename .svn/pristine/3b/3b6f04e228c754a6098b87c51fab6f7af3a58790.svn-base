#include "RNGTest.h"
#include <string>

using namespace std;

int numAttempt = 1000;
int lengthByteArray = 2;

RNGTest::RNGTest(void)
{
}


RNGTest::~RNGTest(void)
{
}

//con 10000 tentativi e 2 byte, RNG_ALGORITHM e RNG_FIPS186_DSA_ALGORITHM impiegano lo stesso tempo
//RNG_DUAL_EC_ALGORITHM invece impiega più di 100 volte di più :-/
TEST_F(RNGTest, GenerateRandomNumber_RNG_ALGORITHM) 
{			
	wstring result1, result2;	
	for(int i=0; i<numAttempt; i++)
	{
		result1 = m_cryptRandomNumberGenerator.Generate(BCRYPT_RNG_ALGORITHM, lengthByteArray);
		result2 = m_cryptRandomNumberGenerator.Generate(BCRYPT_RNG_ALGORITHM, lengthByteArray);	
		ASSERT_NE(result1,result2);
	}		
}

TEST_F(RNGTest, GenerateRandomNumber_RNG_DUAL_EC_ALGORITHM) 
{		
	CryptRandomNumberGenerator rng;
	wstring result1, result2;	
	for(int i=0; i<numAttempt; i++)
	{
		result1 = m_cryptRandomNumberGenerator.Generate(BCRYPT_RNG_DUAL_EC_ALGORITHM, lengthByteArray);
		result2 = m_cryptRandomNumberGenerator.Generate(BCRYPT_RNG_DUAL_EC_ALGORITHM, lengthByteArray);	
		ASSERT_NE(result1,result2);
	}		
}


TEST_F(RNGTest, GenerateRandomNumber_RNG_FIPS186_DSA_ALGORITHM) 
{		
	CryptRandomNumberGenerator rng;
	wstring result1, result2;	
	for(int i=0; i<numAttempt; i++)
	{
		result1 = m_cryptRandomNumberGenerator.Generate(BCRYPT_RNG_FIPS186_DSA_ALGORITHM, lengthByteArray);
		result2 = m_cryptRandomNumberGenerator.Generate(BCRYPT_RNG_FIPS186_DSA_ALGORITHM, lengthByteArray);	
		ASSERT_NE(result1,result2);
	}		
}