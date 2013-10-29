#include "StdAfx.h"
#include "CryptHashingOperation.h"
#include "StringHelper.h"
#include <string>
#include <memory>

using namespace std;

CCryptHashingOperation::CCryptHashingOperation(void)
{
}


CCryptHashingOperation::~CCryptHashingOperation(void)
{
}

wstring CCryptHashingOperation::CalcHashInHexForm(const wstring & messageToHash, const wstring & hashAlgType, int digestLength)
{
	StringHelper stringHelper;
	vector<unsigned char> resultHash;
	resultHash = CreateHash(messageToHash, hashAlgType);
	wstring resultHashToHex = stringHelper.ConvertByteArrayToString(&resultHash[0],digestLength);
	
	return resultHashToHex;
}

vector<unsigned char> CCryptHashingOperation::CalcRawHash(const wstring & messageToHash, const wstring & hashAlgType)
{
	vector<unsigned char> resultHash;
	resultHash = CreateHash(messageToHash, hashAlgType);
	return resultHash;
	
}

vector<unsigned char> CCryptHashingOperation::CreateHash(const wstring & messageToHash, const wstring & hashAlgType)
{
	BCRYPT_ALG_HANDLE phAlgorithm;
	BCRYPT_HASH_HANDLE hHash = NULL;

	PBYTE pbHashObject = NULL;
    PBYTE pbHash = NULL;

	DWORD cbHashObject = 0;
	DWORD cbData = 0;
	DWORD cbHash = 0;
	NTSTATUS res;
	
	vector<unsigned char>  pbBufferCast = ConvertWStringToArrayOfByte(messageToHash);
	int lenBuffer = messageToHash.size();


	res = BCryptOpenAlgorithmProvider(&phAlgorithm, hashAlgType.c_str(), NULL, 0);
	
	 //calculate the size of the buffer to hold the hash object
    res = BCryptGetProperty(phAlgorithm, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbHashObject, sizeof(DWORD), &cbData, 0);

	////allocate the hash object on the heap
 //  
 //   
	pbHashObject = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbHashObject);
    if(NULL == pbHashObject)
    {
        wprintf(L"**** memory allocation failed\n");
    }

 //  //calculate the length of the hash
    res = BCryptGetProperty(phAlgorithm, BCRYPT_HASH_LENGTH, (PBYTE)&cbHash, sizeof(DWORD), &cbData, 0);
 //   
 //   //allocate the hash buffer on the heap
    pbHash = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbHash);
    if(NULL == pbHash)
    {
        wprintf(L"**** memory allocation failed\n");
    }

	res = BCryptCreateHash(phAlgorithm, &hHash, pbHashObject,cbHashObject,NULL,0,0);
	//    
	res = BCryptHashData(hHash, &pbBufferCast[0],lenBuffer,0);
 //   
 //   //close the hash
	if (NULL != pbHash)
		res = BCryptFinishHash(hHash, pbHash, cbHash, 0);

	//
    if(phAlgorithm)
    {
        BCryptCloseAlgorithmProvider(phAlgorithm,0);
    }

    if (hHash)    
    {
        BCryptDestroyHash(hHash);
    }

    if(pbHashObject)
    {
        HeapFree(GetProcessHeap(), 0, pbHashObject);
    }

	vector<unsigned char> dest;
	dest.resize(cbHash);
	

	if(pbHash)
    {
		memcpy(&dest[0], pbHash, cbHash*sizeof(unsigned char));
        HeapFree(GetProcessHeap(), 0, pbHash);
		pbHash = nullptr;
    }
		
	return dest;

}

vector<unsigned char> CCryptHashingOperation::ConvertWStringToArrayOfByte(const wstring & stringToConvert)
{
	size_t lenBuffer = stringToConvert.size();
	
	vector<unsigned char> arrayOfByte;
	arrayOfByte.resize(lenBuffer);
			
	//convert text into BYTE 
	for(size_t i=0; i<lenBuffer;i++)
	{
		arrayOfByte[i] = (unsigned char)stringToConvert.at(i);
	}
	return arrayOfByte;
}

