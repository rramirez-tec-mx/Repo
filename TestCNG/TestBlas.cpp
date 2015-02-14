#include "TestBlas.h"
#include "..\Math\BlasClass.h"

using namespace std;

TestBlas::TestBlas(void)
{
}


TestBlas::~TestBlas(void)
{
}

TEST(TestBlas, testScaleVector)
{
	BlasClass blasClass;
	blasClass.ScaleVector();
}

TEST(TestBlas, testScaleAndSumVector)
{
	BlasClass blasClass;
	blasClass.ScaleAndSumVector();
}

TEST(TestBlas, testScaleAndSumVectorAndSquare)
{
	BlasClass blasClass;
	blasClass.ScaleAndSumVectorAndSquare();
}

TEST(TestBlas, testComputeDistanceAndReturnMax)
{
	BlasClass blasClass;
	double X[3] = { 1, 2, 3 };
	double Y[3] = { 1, 2, 3 };
	double Z[3] = { 1, 2, 3 };
	vector<double> out;
	auto index= blasClass.ComputeDistanceAndReturnMax(X, Y, Z, 3, 2.5, 2.5, 2.5, out);
	cout << "index max " << index << endl;
}

