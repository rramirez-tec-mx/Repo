#include "TestLapack.h"
#include "..\CNG\LapackClass.h"
#include "..\CNG\Matrix.h"

#include <vector>

using namespace std;

TestLapack::TestLapack(void)
{
}


TestLapack::~TestLapack(void)
{
}

TEST(TestLapack, testCalcMatrix)
{
	LapackClass lapackClass;
	lapackClass.calcMatrix();
}

TEST(TestLapack, testCalcMatrix2)
{
	LapackClass lapackClass;

	vector<double> c;
	c.assign(3,0);
	lapackClass.calcMatrix2(&c[0]);
	
}

TEST(TestLapack, calcMatrixProduct)
{
	LapackClass lapackClass;

	
	CMatrix matriceA(3,3);
	
	vector<double> matriceB;
	vector<double> matriceC;
	
	vector<double> columnB1;
	
	matriceA.m_Data[0][0] = 1;
	matriceA.m_Data[0][1] = 5;
	matriceA.m_Data[0][2] = 2;

	matriceA.m_Data[1][0] = 1;
	matriceA.m_Data[1][1] = 2;
	matriceA.m_Data[1][2] = 4;

	matriceA.m_Data[2][0] = 5;
	matriceA.m_Data[2][1] = 3;
	matriceA.m_Data[2][2] = 7;
	
	matriceB.push_back(1);
	matriceB.push_back(1);
	matriceB.push_back(1);

	lapackClass.calcMatrixProduct(matriceA, matriceB, matriceC, 1, 'N', 'N');
}


TEST(TestLapack, calcMatrixInversion)
{
	LapackClass lapackClass;
	vector<double> matriceAFlatten;

	matriceAFlatten.push_back(1);
	matriceAFlatten.push_back(5);
	matriceAFlatten.push_back(2);

	matriceAFlatten.push_back(1);
	matriceAFlatten.push_back(2);
	matriceAFlatten.push_back(4);

	matriceAFlatten.push_back(5);
	matriceAFlatten.push_back(3);
	matriceAFlatten.push_back(7);

	lapackClass.InvertMatrix(matriceAFlatten);
	
	ASSERT_EQ(0.037735849056603731,matriceAFlatten[0]);
	ASSERT_EQ(-0.54716981132075460,matriceAFlatten[1]);
	ASSERT_EQ(0.30188679245283012,matriceAFlatten[2]);

	ASSERT_EQ(0.24528301886792453,matriceAFlatten[3]);
	ASSERT_EQ(-0.056603773584905676,matriceAFlatten[4]);
	ASSERT_EQ(-0.0377358490566037651,matriceAFlatten[5]);

	ASSERT_EQ(-0.13207547169811321,matriceAFlatten[6]);
	ASSERT_EQ(0.41509433962264147,matriceAFlatten[7]);
	ASSERT_EQ(-0.056603773584905648,matriceAFlatten[8]);
}

TEST(TestLapack, calcSingularMatrixInversion)
{
	LapackClass lapackClass;
	vector<double> matriceAFlatten;

	matriceAFlatten.push_back(1);
	matriceAFlatten.push_back(4);
	matriceAFlatten.push_back(7);

	matriceAFlatten.push_back(2);
	matriceAFlatten.push_back(5);
	matriceAFlatten.push_back(8);

	matriceAFlatten.push_back(3);
	matriceAFlatten.push_back(6);
	matriceAFlatten.push_back(9);

	lapackClass.InvertMatrix(matriceAFlatten);
	
	//ASSERT_EQ(0.037735849056603731,matriceAFlatten[0]);
	//ASSERT_EQ(-0.54716981132075460,matriceAFlatten[1]);
	//ASSERT_EQ(0.30188679245283012,matriceAFlatten[2]);

	//ASSERT_EQ(0.24528301886792453,matriceAFlatten[3]);
	//ASSERT_EQ(-0.056603773584905676,matriceAFlatten[4]);
	//ASSERT_EQ(-0.0377358490566037651,matriceAFlatten[5]);

	//ASSERT_EQ(-0.13207547169811321,matriceAFlatten[6]);
	//ASSERT_EQ(0.41509433962264147,matriceAFlatten[7]);
	//ASSERT_EQ(-0.056603773584905648,matriceAFlatten[8]);
}

TEST(TestLapack, calcMatrixProduct2)
{
	LapackClass lapackClass;

	
	CMatrix matriceA(3,3);
	
	vector<double> matriceB;
	vector<double> matriceC;
	
	vector<double> columnB1;
	
	matriceA.m_Data[0][0] = 1;
	matriceA.m_Data[0][1] = 5;
	matriceA.m_Data[0][2] = 2;

	matriceA.m_Data[1][0] = 1;
	matriceA.m_Data[1][1] = 2;
	matriceA.m_Data[1][2] = 4;

	matriceA.m_Data[2][0] = 5;
	matriceA.m_Data[2][1] = 3;
	matriceA.m_Data[2][2] = 7;
	
	matriceB.push_back(1);
	matriceB.push_back(1);
	matriceB.push_back(1);

	matriceB.push_back(2);
	matriceB.push_back(4);
	matriceB.push_back(9);
//
//	>> A = [1 1 5; 5 2 3;2 4 7]
//
//A =
//
//     1     1     5
//     5     2     3
//     2     4     7
//
//>> B = [1 2;1 4;1 9]
//
//B =
//
//     1     2
//     1     4
//     1     9
//
//>> A*B
//
//ans =
//
//     7    51
//    10    45
//    13    83


	lapackClass.calcMatrixProduct(matriceA, matriceB, matriceC, 2, 'n', 'n');

	ASSERT_EQ(7,matriceC[0]);
	ASSERT_EQ(10,matriceC[1]);
	ASSERT_EQ(13,matriceC[2]);

	ASSERT_EQ(51,matriceC[3]);
	ASSERT_EQ(45,matriceC[4]);
	ASSERT_EQ(83,matriceC[5]);
}



