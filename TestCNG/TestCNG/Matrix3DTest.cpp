#include "Matrix3DTest.h"
#include "..\..\CNG\Matrix3D.h"
#include <Windows.h>
#include <ppl.h>
#include "..\..\GeneralCPP\Timer.h"

using namespace std;
using namespace Concurrency;

CMatrix3DTest::CMatrix3DTest(void)
{
}


CMatrix3DTest::~CMatrix3DTest(void)
{
}


TEST(CMatrix3DTest, TestInterp3) 
{
	std::vector<std::vector<double>> matrix3D;
	std::vector<double> depthVector;

	double interpPointX =2.789;
	double interpPointY =2.215;
	double interpPointZ =1.4578;

	std::vector<double> xBreakPts, yBreakPts;

	depthVector.push_back(1);
	depthVector.push_back(2);
	depthVector.push_back(3);
	xBreakPts.push_back(1);
	xBreakPts.push_back(2);
	xBreakPts.push_back(3);
	yBreakPts.push_back(1);
	yBreakPts.push_back(2);
	yBreakPts.push_back(3);

	vector<double> a,b,c;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	a.push_back(8);
	a.push_back(9);

	b.push_back(21);
	b.push_back(22);
	b.push_back(23);
	b.push_back(24);
	b.push_back(25);
	b.push_back(26);
	b.push_back(27);
	b.push_back(28);
	b.push_back(29);

	c.push_back(31);
	c.push_back(32);
	c.push_back(33);
	c.push_back(34);
	c.push_back(35);
	c.push_back(36);
	c.push_back(37);
	c.push_back(38);
	c.push_back(39);

	matrix3D.push_back(a);
	matrix3D.push_back(b);
	matrix3D.push_back(c);
	double out;
					
	CTimer timer;
	timer.Start();	
	out = CMatrix3D::Interp3(matrix3D, depthVector, interpPointX, interpPointY, interpPointZ, xBreakPts, yBreakPts, true);			
	timer.Stop();
		
	ASSERT_NEAR(out,15.59,1e-10);
}

TEST(CMatrix3DTest, TestPerfInterp3_repetitions)
{
	CTimer timer;
	std::vector<std::vector<double>> matrix3D;
	std::vector<double> depthVector;

	double interpPointX =2.789;
	double interpPointY =2.215;
	double interpPointZ =1.4578;

	std::vector<double> xBreakPts, yBreakPts;
	depthVector.push_back(1);
	depthVector.push_back(2);
	depthVector.push_back(3);
	xBreakPts.push_back(1);
	xBreakPts.push_back(2);
	xBreakPts.push_back(3);
	yBreakPts.push_back(1);
	yBreakPts.push_back(2);
	yBreakPts.push_back(3);

	vector<double> a,b,c;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	a.push_back(8);
	a.push_back(9);

	b.push_back(21);
	b.push_back(22);
	b.push_back(23);
	b.push_back(24);
	b.push_back(25);
	b.push_back(26);
	b.push_back(27);
	b.push_back(28);
	b.push_back(29);

	c.push_back(31);
	c.push_back(32);
	c.push_back(33);
	c.push_back(34);
	c.push_back(35);
	c.push_back(36);
	c.push_back(37);
	c.push_back(38);
	c.push_back(39);

	matrix3D.push_back(a);
	matrix3D.push_back(b);
	matrix3D.push_back(c);
	vector<double> out1,out2;
	vector<double> interPointXVector,interPointYVector, interPointZVector;
	size_t repetitions = 20000;
	out1.resize(repetitions);
	out2.resize(repetitions);
	interPointXVector.resize(repetitions);
	interPointYVector.resize(repetitions);
	interPointZVector.resize(repetitions);

	for(size_t i=0; i<repetitions; i++)
	{
			double currentIt = (double)i/(double)repetitions;
			interPointXVector[i] = currentIt*(xBreakPts[xBreakPts.size()-1] - xBreakPts[0]);
			interPointYVector[i] = currentIt*(yBreakPts[yBreakPts.size()-1] - yBreakPts[0]);
			interPointZVector[i] = currentIt*(depthVector[depthVector.size()-1] - depthVector[0]);
	}
		
	cout << "Start esecuzione di " << repetitions << " interpolazioni sequenziali su cubo di dimensione " << xBreakPts.size() << "x" << yBreakPts.size() << "x" << depthVector.size()  ;
	timer.Start();
	for (size_t k=0; k < repetitions; k++)
	out1[k] = CMatrix3D::Interp3(matrix3D, depthVector, interPointXVector[k], interPointYVector[k], interPointZVector[k], xBreakPts, yBreakPts, true);			
	timer.Stop();
	
	cout << "Start esecuzione di " << repetitions << " interpolazioni parallele su cubo di dimensione " << xBreakPts.size() << "x" << yBreakPts.size() << "x" << depthVector.size()  << endl;
	timer.Start();
	parallel_for (size_t(0), repetitions, [&](size_t i)
	{
		out2[i] = CMatrix3D::Interp3(matrix3D, depthVector,  interPointXVector[i], interPointYVector[i], interPointZVector[i], xBreakPts, yBreakPts, true);
	});
	timer.Stop();
	

}

TEST(CMatrix3DTest, TestInterp3InverseRowWise) 
{
	std::vector<std::vector<double>> matrix3D;
	std::vector<double> depthVector;

	double interpPointX =2.789;
	double interpPointY =15.59;
	double interpPointZ =1.4578;

	std::vector<double> xBreakPts, yBreakPts;

	depthVector.push_back(1);
	depthVector.push_back(2);
	depthVector.push_back(3);
	xBreakPts.push_back(1);
	xBreakPts.push_back(2);
	xBreakPts.push_back(3);
	yBreakPts.push_back(1);
	yBreakPts.push_back(2);
	yBreakPts.push_back(3);

	vector<double> a,b,c;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	a.push_back(8);
	a.push_back(9);

	b.push_back(21);
	b.push_back(22);
	b.push_back(23);
	b.push_back(24);
	b.push_back(25);
	b.push_back(26);
	b.push_back(27);
	b.push_back(28);
	b.push_back(29);

	c.push_back(31);
	c.push_back(32);
	c.push_back(33);
	c.push_back(34);
	c.push_back(35);
	c.push_back(36);
	c.push_back(37);
	c.push_back(38);
	c.push_back(39);
	

	matrix3D.push_back(a);
	matrix3D.push_back(b);
	matrix3D.push_back(c);
	double out;
					
	CTimer timer;
	timer.Start();	
	out = CMatrix3D::Interp3Inverse(matrix3D, depthVector, interpPointX, interpPointY, interpPointZ, xBreakPts, yBreakPts, 'y', true);			
	timer.Stop();
		
	ASSERT_NEAR(out,2.215,1e-10);


	interpPointX =15.59;
	interpPointY =2.215;
	interpPointZ =1.4578;
	out = CMatrix3D::Interp3Inverse(matrix3D, depthVector, interpPointX, interpPointY, interpPointZ, xBreakPts, yBreakPts, 'x', true);			

	ASSERT_NEAR(out,2.789,1e-10);
}


TEST(CMatrix3DTest, TestInterp3InverseColumnWise) 
{
	std::vector<std::vector<double>> matrix3D;
	std::vector<double> depthVector;

	double interpPointX =2.789;
	double interpPointY =15.59;
	double interpPointZ =1.4578;

	std::vector<double> xBreakPts, yBreakPts;

	depthVector.push_back(1);
	depthVector.push_back(2);
	depthVector.push_back(3);
	xBreakPts.push_back(1);
	xBreakPts.push_back(2);
	xBreakPts.push_back(3);
	yBreakPts.push_back(1);
	yBreakPts.push_back(2);
	yBreakPts.push_back(3);

	vector<double> a,b,c;

	a.push_back(1);
	a.push_back(4);
	a.push_back(7);
	a.push_back(2);
	a.push_back(5);
	a.push_back(8);
	a.push_back(3);
	a.push_back(6);
	a.push_back(9);

	b.push_back(21);
	b.push_back(24);
	b.push_back(27);
	b.push_back(22);
	b.push_back(25);
	b.push_back(28);
	b.push_back(23);
	b.push_back(26);
	b.push_back(29);

	c.push_back(31);
	c.push_back(34);
	c.push_back(37);
	c.push_back(32);
	c.push_back(35);
	c.push_back(38);
	c.push_back(33);
	c.push_back(36);
	c.push_back(39);
	

	matrix3D.push_back(a);
	matrix3D.push_back(b);
	matrix3D.push_back(c);
	double out;
					
	CTimer timer;
	timer.Start();	
	out = CMatrix3D::Interp3Inverse(matrix3D, depthVector, interpPointX, interpPointY, interpPointZ, xBreakPts, yBreakPts, 'y', false);			
	timer.Stop();
		
	ASSERT_NEAR(out,2.215,1e-10);


	interpPointX =15.59;
	interpPointY =2.215;
	interpPointZ =1.4578;
	out = CMatrix3D::Interp3Inverse(matrix3D, depthVector, interpPointX, interpPointY, interpPointZ, xBreakPts, yBreakPts, 'x', false);			

	ASSERT_NEAR(out,2.789,1e-10);
}

TEST(CMatrix3DTest, TestInterp3Inverse_repetitions)
{
	std::vector<std::vector<double>> matrix3D;
	std::vector<double> depthVector;

	double interpPointX = 2.789;
	double interpPointY = 15.59;
	double interpPointZ = 1.4578;

	std::vector<double> xBreakPts, yBreakPts;

	depthVector.push_back(1);
	depthVector.push_back(2);
	depthVector.push_back(3);
	xBreakPts.push_back(1);
	xBreakPts.push_back(2);
	xBreakPts.push_back(3);
	yBreakPts.push_back(1);
	yBreakPts.push_back(2);
	yBreakPts.push_back(3);

	vector<double> a, b, c;

	a.push_back(1);
	a.push_back(4);
	a.push_back(7);
	a.push_back(2);
	a.push_back(5);
	a.push_back(8);
	a.push_back(3);
	a.push_back(6);
	a.push_back(9);

	b.push_back(21);
	b.push_back(24);
	b.push_back(27);
	b.push_back(22);
	b.push_back(25);
	b.push_back(28);
	b.push_back(23);
	b.push_back(26);
	b.push_back(29);

	c.push_back(31);
	c.push_back(34);
	c.push_back(37);
	c.push_back(32);
	c.push_back(35);
	c.push_back(38);
	c.push_back(33);
	c.push_back(36);
	c.push_back(39);


	matrix3D.push_back(a);
	matrix3D.push_back(b);
	matrix3D.push_back(c);
	vector<double> out1;
	size_t repetitions = 20000;
	vector<double> interPointXVector, interPointYVector, interPointZVector;
	out1.resize(repetitions);
	interPointXVector.resize(repetitions);
	interPointYVector.resize(repetitions);
	interPointZVector.resize(repetitions);

	for (size_t i = 0; i<repetitions; i++)
	{
		double currentIt = (double)i / (double)repetitions;
		interPointXVector[i] = currentIt*(xBreakPts[xBreakPts.size() - 1] - xBreakPts[0]);
		interPointYVector[i] = currentIt*(yBreakPts[yBreakPts.size() - 1] - yBreakPts[0]);
		interPointZVector[i] = currentIt*(depthVector[depthVector.size() - 1] - depthVector[0]);
	}

	CTimer timer;
	timer.Start();
	for (size_t k = 0; k < repetitions; k++)
	out1[k] = CMatrix3D::Interp3Inverse(matrix3D, depthVector, interpPointX, interpPointY, interpPointZ, xBreakPts, yBreakPts, 'y', false);
	timer.Stop();
}
