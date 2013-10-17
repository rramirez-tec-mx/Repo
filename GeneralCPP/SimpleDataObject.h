#pragma once
#include <string>
#define DLL_EXPORT __declspec(dllexport)



class DLL_EXPORT CSimpleDataObject
{
public:
	CSimpleDataObject(double frontRH, double rearRH, double uOnV, double m1, double m2);
	~CSimpleDataObject(void);

	typedef enum ElencoPolicies {ciccio=1, paperino=2};

	void PassString(std::string mystring);
	void PassStringByRef(const std::string & mystring);

private :
	double m_RHF;
	double m_RHR;
	double m_UonV;
	double m_1;
	double m_2;
	
public:
	double GetRHF();
	double GetRHR();
	double GetUonV();
	ElencoPolicies policy;
};

