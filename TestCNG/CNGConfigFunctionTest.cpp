#include "CNGConfigFunctionTest.h"
#include "..\CNG\CNG.h"
#include "..\CNG\CryptEnumerator.h"
#include <Windows.h>

using namespace std;


CNGConfigFunctionTest::CNGConfigFunctionTest(void)
{
}


CNGConfigFunctionTest::~CNGConfigFunctionTest(void)
{
}


TEST(CNGConfigFunctionTest, CheckFipsIsEnabled) 
{
	CNG cng;
	ASSERT_EQ(cng.CheckIfFipsIsEnabled(),0);
}


TEST(CNGConfigFunctionTest, EnumCryptoAlgorithm) 
{
	CCryptEnumerator cryptEnumerator;
	string message = "algoritmo di cifratura";
	cryptEnumerator.PrintAlgorithm(BCRYPT_CIPHER_OPERATION,  message);

	message = "algoritmo di hashing";
	cryptEnumerator.PrintAlgorithm(BCRYPT_HASH_OPERATION,  message);
	 
	message = "algoritmo per operazioni di cifratura asimmetrica";
	cryptEnumerator.PrintAlgorithm(BCRYPT_ASYMMETRIC_ENCRYPTION_OPERATION,  message);
	 
	message = "algoritmo per operazioni di condivisione di un segreto";
	cryptEnumerator.PrintAlgorithm(BCRYPT_SECRET_AGREEMENT_OPERATION,  message);
	
	message = "algoritmo per operazioni di firma digitale";
	cryptEnumerator.PrintAlgorithm(BCRYPT_SIGNATURE_OPERATION,  message);
	
	message = "algoritmo per operazioni gnerazione numero casuale";
	cryptEnumerator.PrintAlgorithm(BCRYPT_RNG_OPERATION,  message);
}

TEST(CNGConfigFunctionTest, EnumCryptoProvider)
{
	CCryptEnumerator cryptEnumerator;
	string message = "provider 3DES";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_3DES_ALGORITHM), message);

	message = "provider 3DES_112";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_3DES_112_ALGORITHM), message);

	message = "provider AES";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_AES_ALGORITHM), message);
	
	message = "provider AES GMAC";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_AES_GMAC_ALGORITHM), message);
	
	message = "provider DES";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_DES_ALGORITHM), message);
	
	message = "provider DESX";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_DESX_ALGORITHM), message);
	
	message = "provider DH Diffie Helmann";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_DH_ALGORITHM), message);
		
	message = "provider DSA digital signature algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_DSA_ALGORITHM), message);

	message = "provider ECDH 256-bit prime elliptic curve Diffie-Hellman key exchange algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_ECDH_P256_ALGORITHM), message);

	message = "provider ECDH 384-bit prime elliptic curve Diffie-Hellman key exchange algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_ECDH_P384_ALGORITHM), message);

	message = "provider ECDH 524-bit prime elliptic curve Diffie-Hellman key exchange algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_ECDH_P521_ALGORITHM), message);

	message = "provider ECDH 256-bit prime elliptic curve digital signature algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_ECDSA_P256_ALGORITHM), message);

	message = "provider ECDH 384-bit prime elliptic curve digital signature algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_ECDSA_P384_ALGORITHM), message);

	message = "provider ECDH 524-bit prime elliptic curve digital signature algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_ECDSA_P521_ALGORITHM), message);

	message = "provider MD2 hash algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_MD2_ALGORITHM), message);

	message = "provider MD4 hash algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_MD4_ALGORITHM), message);

	message = "provider MD5 hash algorithm";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_MD5_ALGORITHM), message);

	message = "provider RC2";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_RC2_ALGORITHM), message);

	message = "provider RC4";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_RC4_ALGORITHM), message);
	
	message = "provider RNG random number generator";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_RNG_ALGORITHM), message);
	
	message = "provider dual elliptic curve random-number generator";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_RNG_DUAL_EC_ALGORITHM), message);
	
	message = "random-number generator algorithm suitable for DSA";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_RNG_FIPS186_DSA_ALGORITHM), message);
	
	message = "RSA";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_RSA_ALGORITHM), message);
	
	message = "The RSA signature algorithm. This algorithm is not currently supported. You can use the BCRYPT_RSA_ALGORITHM";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_RSA_SIGN_ALGORITHM), message);

	message = "SHA1 hashing";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_SHA1_ALGORITHM), message);

	message = "SHA256 hashing";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_SHA256_ALGORITHM), message);

	message = "SHA384 hashing";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_SHA384_ALGORITHM), message);

	message = "SHA512 hashing";
	cryptEnumerator.PrintProvider(wstring(BCRYPT_SHA512_ALGORITHM), message);
}