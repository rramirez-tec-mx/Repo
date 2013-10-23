#pragma once
#include <string>
#include "GeneralCPPExport.h"

class GENERALCPP_EXPORTS_API CSimpleDataObject
{
public:
	CSimpleDataObject(double val1, double val2, double val3, double m1, double m2);
	~CSimpleDataObject(void);

	typedef enum ElencoPolicies {ciccio=1, paperino=2};

	void PassString(std::string mystring);
	void PassStringByRef(const std::string & mystring);

private :
	double m_val1;
	double m_val2;
	double m_val3;
	double m_1;
	double m_2;
	
public:
	double GetVal1();
	double GetVal2();
	double GetVal3();
	ElencoPolicies policy;
};

