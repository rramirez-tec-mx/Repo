#pragma once
#include "openssl\md5.h"
//#ifdef  __cplusplus
//extern "C" {
//#endif
//	
//#ifdef  __cplusplus
//}
//#endif

class MD5Hash
{
public:
	MD5Hash();
	~MD5Hash();
	void Do();
};


