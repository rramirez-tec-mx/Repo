#include "StdAfx.h"
#include "SimpleDataObject.h"

CSimpleDataObject::CSimpleDataObject()
{

}

CSimpleDataObject::CSimpleDataObject(double val1, double val2, double val3, double m1, double m2):m_val1(val1),m_val2(val2),m_val3(val3),m_1(m1), m_2(m2)
{
}


CSimpleDataObject::~CSimpleDataObject(void)
{
}


double CSimpleDataObject::GetVal1()
{
	return m_val1;
}
double CSimpleDataObject::GetVal2()
{
	return m_val2;
}

double CSimpleDataObject::GetVal3()
{
	return m_val3;
}

void CSimpleDataObject::PassString(std::string mystring)
{
	return;
}

void CSimpleDataObject::PassStringByRef(const std::string & )
{
	return;
}

void CSimpleDataObject::X_aligned_memcpy_sse2(void* dest, const void* src, const unsigned long size_t)
{

	__asm
	{
		mov esi, src;    //src pointer
		mov edi, dest;   //dest pointer

		mov ebx, size_t; //ebx is our counter 
		shr ebx, 7;      //divide by 128 (8 * 128bit registers)


	loop_copy:
		prefetchnta 128[ESI]; //SSE2 prefetch
		prefetchnta 160[ESI];
		prefetchnta 192[ESI];
		prefetchnta 224[ESI];

		movdqa xmm0, 0[ESI]; //move data from src to registers
		movdqa xmm1, 16[ESI];
		movdqa xmm2, 32[ESI];
		movdqa xmm3, 48[ESI];
		movdqa xmm4, 64[ESI];
		movdqa xmm5, 80[ESI];
		movdqa xmm6, 96[ESI];
		movdqa xmm7, 112[ESI];

		movntdq 0[EDI], xmm0; //move data from registers to dest
		movntdq 16[EDI], xmm1;
		movntdq 32[EDI], xmm2;
		movntdq 48[EDI], xmm3;
		movntdq 64[EDI], xmm4;
		movntdq 80[EDI], xmm5;
		movntdq 96[EDI], xmm6;
		movntdq 112[EDI], xmm7;

		add esi, 128;
		add edi, 128;
		dec ebx;

		jnz loop_copy; //loop please
	//loop_copy_end:
	}
}