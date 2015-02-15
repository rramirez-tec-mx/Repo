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

TEST(TestBlas, testComputeDistanceAndReturnMin)
{
	BlasClass blasClass;
	CTimer timer;
	size_t rep = 5000;
	vector<double> X, Y, Z;
	vector<double> minusOne;
	for (size_t i = 0; i < rep; i++)
	{
		X.push_back(i);
		Y.push_back(i);
		Z.push_back(i);
		minusOne.push_back(-1);
	}
	vector<double> out;
	out.resize(rep);
	memset(&out[0], 0, rep*sizeof(double));
	double xc = 4;
	double yc = 4;
	double zc = 4;
	timer.Start();
	//auto index= blasClass.ComputeDistanceAndReturnMax(X, Y, Z, 3, 2.5, 2.5, 2.5, out);
	auto index = blasClass.ComputeDistanceAndReturnMin(&X[0], &Y[0], &Z[0], rep, xc, yc, zc, minusOne, out);
	timer.Stop();
	cout << "index min " << index << endl;
	getchar();

}

