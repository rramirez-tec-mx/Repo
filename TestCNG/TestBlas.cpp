#include "TestBlas.h"
#include "..\Math\BlasClass.h"
#include "..\GeneralCPP\Timer.h"

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
	CTimer timer;
	size_t rep = 5000;

	//double X[3] = { 1, 2, 3 };
	//double Y[3] = { 1, 2, 3 };
	//double Z[3] = { 1, 2, 3 };

	vector<double> X, Y, Z;
	vector<double> minusOne;
	for (size_t i = 0; i < rep; i++)
	{
		X.push_back(i + 1);
		Y.push_back(i + 1);
		Z.push_back(i + 1);
		minusOne.push_back(-1);
	}
	vector<double> out;
	out.resize(rep);
	memset(&out[0], 0, rep*sizeof(double));

	timer.Start();
	//auto index= blasClass.ComputeDistanceAndReturnMax(X, Y, Z, 3, 2.5, 2.5, 2.5, out);
	auto index = blasClass.ComputeDistanceAndReturnMax(&X[0], &Y[0], &Z[0], rep, 2.5, 2.5, 2.5, minusOne, out);
	timer.Stop();
	cout << "index max " << index << endl;

	getchar();
}

