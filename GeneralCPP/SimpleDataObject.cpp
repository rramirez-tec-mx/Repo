#include "StdAfx.h"
#include "SimpleDataObject.h"


CSimpleDataObject::CSimpleDataObject(double frontRH, double rearRH, double uOnV, double m1, double m2):m_RHF(frontRH),m_RHR(rearRH),m_UonV(uOnV),m_1(m1), m_2(m2)
{
}


CSimpleDataObject::~CSimpleDataObject(void)
{
}


double CSimpleDataObject::GetRHF()
{
	return m_RHF;
}
double CSimpleDataObject::GetRHR()
{
	return m_RHR;
}

double CSimpleDataObject::GetUonV()
{
	return m_UonV;
}

	