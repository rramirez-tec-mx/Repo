#include "GeneralCPPTest.h"
#include <bitset>
#include <locale>
#include <iostream>
#include <tchar.h>
#include <sstream>
#include "..\GeneralCPP\SimpleDataObject.h"
#include "..\GeneralCPP\Timer.h"
#include "..\GeneralCPP\SimplePOD.h"
#include "..\GeneralCPP\Singleton.h"
#include "..\GeneralCPP\WindowsVersion.h"
#include <windows.h>
#include <memory>
#include <tchar.h>
#include <algorithm>
#include <map>

using namespace std;

#pragma intrinsic (memcpy)

#define CAMPOOFFSET(type, field)    ((int)(&((type near*)1)->field)-1)
#define FO(f) CAMPOOFFSET(SimplePOD, f)

CGeneralCPPTest::CGeneralCPPTest(void)
{
}


CGeneralCPPTest::~CGeneralCPPTest(void)
{
}

TEST(CNGConfigFunctionTest, TestPerformance) 
{
	CTimer timer;
	ostringstream pippo;
	
	int iteration = 100000;

	timer.Start();
	for(int i=0; i< iteration; i++)
	{
		double val1 = i*2.3;
		double val2 = i*4.7;
		double val3 = i*5.378;
		pippo << val1 << "|" << val2 << "|" << val3 << endl;
	}
	timer.Stop();

	char buffer1[100];
	char buffer2[100];
	char buffer3[100];
	timer.Start();
	for(int i=0; i< iteration; i++)
	{
		double val1 = i*2.3;
		double val2 = i*4.7;
		double val3 = i*5.378;
		sprintf_s(buffer1,"%g",val1);
		sprintf_s(buffer2,"%g",val2);
		sprintf_s(buffer3,"%g",val3);
	}
	timer.Stop();

	
}

TEST(CNGConfigFunctionTest, TestHash) 
{
	//setlocale( LC_ALL, "English" ); 
	locale loc;
  
	int len = 3;
	double p1[3] = {2.5,0.7,1.0};
	double p2[3] = {2.5,0.7,1.5};

   string s1,s2;
   
   s1.assign((char*)&p1,len*sizeof(double));
   s2.assign((char*)&p2,3*sizeof(double));

   use_facet< collate<_TCHAR> > ( loc ).hash (s1.data(), s1.data()+s1.length());
   use_facet< collate<_TCHAR> > ( loc ).hash (s2.data(), s2.data()+ s2.length());


   CSimpleDataObject o1(2.5, 0.7, 1.0, 0, 7);
   CSimpleDataObject o2(2.5, 0.7, 1.5, 0, 0);
   string s3, s4;
   s3.assign((_TCHAR*)&o1,sizeof(CSimpleDataObject));
   s4.assign((_TCHAR*)&o2,sizeof(CSimpleDataObject)); 

   string s5 = s3+s4;
   string s6 = s4+s3;

   for(int i =0;i< (int)s5.size(); i++)
   {
	   if(s5[i]!=s6[i])
	   {
		   printf("Trovato carattere diverso %c %c posizione %d\n",s5[i],s6[i],i);
	   }
   }

   use_facet< collate<_TCHAR> > ( loc ).hash (s3.data(), s3.data()+s3.length());
   use_facet< collate<_TCHAR> > ( loc ).hash (s4.data(), s4.data()+ s4.length());
   use_facet< collate<_TCHAR> > ( loc ).hash (s5.data(), s5.data()+ s5.length());
   use_facet< collate<_TCHAR> > ( loc ).hash (s6.data(), s6.data()+ s6.length());



   char b1[100];
   char b2[100];
   sprintf_s(b1,"%f%f%f",p1[0], p1[1], p1[2]);
   sprintf_s(b2,"%f%f",p2[0], p2[1]);
   string s7(b1);
   string s8(b2);
   use_facet< collate<_TCHAR> > ( loc ).hash (s7.data(), s7.data()+ s7.length());
   use_facet< collate<_TCHAR> > ( loc ).hash (s8.data(), s8.data()+ s8.length());
      
}


TEST(CNGConfigFunctionTest, TestBitWise) 
{
	int value = 0x00;
	int bitwise1 = 0x00000001; //1 
	int bitwise2 = 0x00000010; //16
	int bitwise3 = 0x00000100; // 256
	
	value = 257;
	printf("value %d bitwise1 = %d \n", value, (value&bitwise1)==bitwise1);
	printf("value %d bitwise2 = %d \n", value, (value&bitwise2)==bitwise2);
	printf("value %d bitwise3 = %d \n", value, (value&bitwise3)==bitwise3);

	if(!((value&bitwise2)==bitwise2))
		value = value + bitwise2;
	printf("value %d bitwise2 = %d \n", value, (value&bitwise2)==bitwise2);

}

TEST(CNGConfigFunctionTest, TestSwitchCase) 
{
	int cmd = 2;
	float a = 4;
	float b = 2;
	float ret = 0;

	switch (cmd)
	{
		case 1:
			ret = a+b;
		break;
		case 2:
			ret = a-b;
		break;
		case 3:
			ret = a*b;
		break;
		case 4:
			if(b!=0)
				ret = a/b;
			else
				ret = 0;
		break;
		default:
			ret = 0;
	}

	printf("scelta %d): risultato = %f\n", cmd, ret);
}




TEST(CNGConfigFunctionTest, TestUniquePtr) 
{
	
	int leng = 2;
	unique_ptr<double[]> ptrdouble = unique_ptr<double[]>(new double[leng]);

	ptrdouble[0] = 1;
	ptrdouble[1] = 2;
	
	
	for(int i=0;i<leng;i++)
	cout << " val["<< i <<"] = "<< ptrdouble[i] << endl;

	ptrdouble.reset();
	ptrdouble.reset();
}

TEST(CNGConfigFunctionTest, TestPerformanceCopy) 
{
	CTimer timer;
	SimplePOD pod1;
	SimplePOD pod2;
	timer.Start();
	for (int i=0;i<10000;i++)
		pod2 = pod1;
	timer.Stop();
}


TEST(CNGConfigFunctionTest, TestDoubleVersusFloat) 
{
	double afromCat = 1.581421362458969;
	double bfromCat = 1.471987469247834;
	double cfromCat = 1.474228888474931;
	double longdob = 99.5441117107108710;
	printf(" Conti fra double: %g\n", afromCat * bfromCat * cfromCat);
	
	printf(" Conti fra float: %f\n" , (float)afromCat * (float)bfromCat * (float)cfromCat);

	printf(" Longdouble: %lg\n", longdob);

}

TEST(CNGConfigFunctionTest, TestCopyStdVector) 
{
	SimplePOD pod1;
	SimplePOD pod2;

	pod2 = pod1;
}

TEST(CNGConfigFunctionTest, TestMemCpyPerformance) 
{
	double *in;
	vector<double> out1,out2;

	int size = 400;
	in = new double[size];
	memset(in, 0, size*sizeof(double));
	out1.resize(size);
	CTimer timer;
	timer.Start();
	memcpy(&out1[0], in, size*sizeof(double));	
	timer.GetElapsedTimeInMicros();
	delete[] in;


	size = 3000;
	in = new double[size];
	memset(in, 0, size*sizeof(double));
	out2.resize(size);	
	timer.Start();
	memcpy(&out2[0], in, size*sizeof(double));	
	timer.GetElapsedTimeInMicros();
	delete[] in;
}

TEST(CNGConfigFunctionTest, TestPerf1) 
{
	double *a;
	double *b;
	double *c;

	CTimer timer;
	timer.Start();
	for(int i=0;i < 10000;i++)
	{
		a = new double[100];
		memset(a, 0, 100*sizeof(double));
		b = new double[100];
		memset(b, 0, 100 * sizeof(double));
		c = new double[100];
		memset(c, 0, 100 * sizeof(double));

		for (int j=0; j< 100; j++)
		{
			a[j] = b[j]*c[j];
			a[j] = 6*b[j];
		}

		delete[] a;
		delete[] b;
		delete[] c;
	}
	timer.GetElapsedTimeInMicros();
	
}


TEST(CNGConfigFunctionTest, TestPerf2) 
{
	double *a;
	double *b;
	double *c;

	CTimer timer;
	timer.Start();
	a = new double[100];
	b = new double[100];
	c = new double[100];
	for(int i=0;i < 10000;i++)
	{
		

		for (int j=0; j< 100; j++)
		{
			a[j] = b[j]*c[j];
			a[j] = 6*b[j];
		}

		
	}
	delete[] a;
	delete[] b;
	delete[] c;
	timer.GetElapsedTimeInMicros();
	
}

TEST(CNGConfigFunctionTest, TestMemSet) 
{
	double *p;
	p = new double[10];

	memset(p, 1, 10*sizeof(double));
	delete[] p;
}

TEST(CNGConfigFunctionTest, TestSetDll) 
{
	//DLL_DIRECTORY_COOKIE caz;
	//PCWSTR stringa = L"ciao";
	////caz = AddDllDirectory( 
}

TEST(CNGConfigFunctionTest, TestAlgorithm) 
{
	std::vector<double> vec;
	std::vector<double>::iterator low,high;
	double val = 20;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	if(val <= vec[0])
	{
		cout << " min e max saturati a " << vec[0] <<endl;
		return;
	}

	if(val >= vec[vec.size()-1])
	{
		cout << " min e max saturati a " << vec[vec.size()-1] << endl;
		return;
	}
	
	high=std::upper_bound(vec.begin(), vec.end(), val);	
	cout << "il range per " << val << " e' ["<< vec[high - vec.begin() -1] << "," << vec[high - vec.begin()] << "]"  << endl;

	
}

TEST(CNGConfigFunctionTest, TestMemoryUsage) 
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);

	// Use to convert bytes to KB
#define DIV 1024

// Specify the width of the field in which to print the numbers. 
// The asterisk in the format specifier "%*I64d" takes an integer 
// argument and uses it to pad and right justify the number.
#define WIDTH 7

  GlobalMemoryStatusEx (&statex);

  _tprintf(TEXT("There is  %*ld percent of memory in use.\n"), WIDTH, statex.dwMemoryLoad);
  
  _tprintf (TEXT("There are %*I64d total KB of physical memory.\n"),
            WIDTH, statex.ullTotalPhys/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of physical memory.\n"),
            WIDTH, statex.ullAvailPhys/DIV);
  _tprintf (TEXT("There are %*I64d total KB of paging file.\n"),
            WIDTH, statex.ullTotalPageFile/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of paging file.\n"),
            WIDTH, statex.ullAvailPageFile/DIV);
  _tprintf (TEXT("There are %*I64d total KB of virtual memory.\n"),
            WIDTH, statex.ullTotalVirtual/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of virtual memory.\n"),
            WIDTH, statex.ullAvailVirtual/DIV);

  // Show the amount of extended memory available.

  _tprintf (TEXT("There are %*I64d free  KB of extended memory.\n"),
            WIDTH, statex.ullAvailExtendedVirtual/DIV);
  ULONGLONG TotalMemoryInKilobytes;
  GetPhysicallyInstalledSystemMemory(&TotalMemoryInKilobytes);

  
  _tprintf (TEXT("There are %*I64d free  MB of memory.\n"),
            WIDTH, (TotalMemoryInKilobytes/1024));
	
}


TEST(CNGConfigFunctionTest, TestCopyStringPerf) 
{
	CSimpleDataObject obj(0,0,0,0,0);
	string message = "ciao";
	size_t repetitions = 10000;;

	CTimer timer;

	cout << "Start profiling with copy of " << repetitions << " string" << endl;
	timer.Start();
	for (size_t k =0; k< repetitions; k++)
		obj.PassString(message);
	timer.GetElapsedTimeInMicros();

	cout << endl;

	cout << "Start profiling with references of " << repetitions << " string" << endl;	
	timer.Start();
	for (size_t k =0; k< repetitions; k++)
		obj.PassStringByRef(message);

	timer.GetElapsedTimeInMicros();	
}


TEST(CNGConfigFunctionTest, TestSScanf_dest_lower_than_source_secure)
{
	char *src = "ciaociao";
	char out[4];
	sscanf_s(src, "%s", out, _countof(out));
	ASSERT_STREQ(out, "");
}

TEST(CNGConfigFunctionTest, TestSScanf_dest_bigger_than_source_secure)
{
	char *src = "ciaociao";
	char out[20];
	sscanf_s(src, "%s", out, _countof(out));
	ASSERT_STREQ(out, "ciaociao");
}

TEST(CNGConfigFunctionTest, TestSingleton)
{
	Singleton *sc1;
	sc1 = Singleton::getInstance();
	Singleton::DestroyInstance();
}


TEST(CNGConfigFunctionTest, TestGetVersion)
{
	map<size_t, bool> enumVersion = WindowsVersion().FillMapOfWindowsVersion();
	
	ASSERT_EQ(true, enumVersion[WindowsVersion::WINXP_OR_GREATER]);
	ASSERT_EQ(true, enumVersion[WindowsVersion::WINXP_SP2_OR_GREATER]);
	ASSERT_EQ(true, enumVersion[WindowsVersion::WINXP_SP3_OR_GREATER]);
	ASSERT_EQ(true, enumVersion[WindowsVersion::WINVISTA_OR_GREATER]);
	ASSERT_EQ(true, enumVersion[WindowsVersion::WINVISTA_SP1_OR_GREATER]);
	ASSERT_EQ(true, enumVersion[WindowsVersion::WINVISTA_SP2_OR_GREATER]);
	ASSERT_EQ(true, enumVersion[WindowsVersion::WINSEVEN_OR_GREATER]);
	ASSERT_EQ(true, enumVersion[WindowsVersion::WINSEVEN_SP1_OR_GREATER]);
	ASSERT_EQ(true, enumVersion[WindowsVersion::WINEIGHT_OR_GREATER]);
	ASSERT_EQ(false, enumVersion[WindowsVersion::WINEIGHT_POINT1_OR_GREATER]);
	ASSERT_EQ(false, enumVersion[WindowsVersion::WIN_SERVER]);
}

