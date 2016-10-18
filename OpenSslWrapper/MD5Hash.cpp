#include "MD5Hash.h"



MD5Hash::MD5Hash()
{
}


MD5Hash::~MD5Hash()
{
}

void MD5Hash::Do()
{
	//const unsigned char in[6]= "guido";
	//unsigned char *out = nullptr;

	//char *key = "my key";
	//AES_KEY aes_key;

	//AES_set_encrypt_key((unsigned char*)key, 128, &aes_key);

	//AES_encrypt(in, out, &aes_key);

	//AES_decrypt(in, out, &aes_key);

	unsigned char * out;
	const unsigned char *d = nullptr;
	size_t n = 128;
	unsigned char *md = nullptr;
	out = MD5(d, n, md);
	
}