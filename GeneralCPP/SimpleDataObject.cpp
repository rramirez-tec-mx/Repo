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

