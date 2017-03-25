//#include "TestBlas.h"
//#include "..\Math\BlasClass.h"
//#include "..\GeneralCPP\Timer.h"
//
//using namespace std;
//
//TestBlas::TestBlas(void)
//{
//}
//
//
//TestBlas::~TestBlas(void)
//{
//}
//
//TEST(TestBlas, testScaleVector)
//{
//	BlasClass blasClass;
//	blasClass.ScaleVector();
//}
//
//TEST(TestBlas, testScaleAndSumVector)
//{
//	BlasClass blasClass;
//	blasClass.ScaleAndSumVector();
//}
//
//TEST(TestBlas, testScaleAndSumVectorAndSquare)
//{
//	BlasClass blasClass;
//	blasClass.ScaleAndSumVectorAndSquare();
//}
//
////TEST(TestBlas, testComputeDistanceAndReturnMin)
////{
////	BlasClass blasClass;
////	CTimer timer;
////	size_t rep = 5000;
////	vector<double> X, Y, Z;
////	vector<double> X1, Y1, Z1;
////	vector<double> minusOne;
////	for (size_t i = 0; i < rep; i++)
////	{
////		double data = (double)i;
////		X.push_back(data);
////		Y.push_back(data);
////		Z.push_back(data);
////		X1.push_back(data);
////		Y1.push_back(data);
////		Z1.push_back(data);
////		minusOne.push_back(-1);
////	}
////	vector<double> out;
////	out.resize(rep);
////	memset(&out[0], 0, rep*sizeof(double));
////	double xc = 15;
////	double yc = 15;
////	double zc = 15;
////	timer.Start();
////	//auto index= blasClass.ComputeDistanceAndReturnMax(X, Y, Z, 3, 2.5, 2.5, 2.5, out);
////	auto index1 = blasClass.ComputeDistanceAndReturnMin(&X[0], &Y[0], &Z[0], rep, xc, yc, zc, minusOne, out);	
////	timer.Stop();
////	cout << "index min veloce " << index1 << endl;
////	memset(&out[0], 0, rep*sizeof(double));
////	timer.Start();
////	//auto index= blasClass.ComputeDistanceAndReturnMax(X, Y, Z, 3, 2.5, 2.5, 2.5, out);	
////	auto index2 = blasClass.ComputeDistanceAndReturnMinMale(&X1[0], &Y1[0], &Z1[0], rep, xc, yc, zc, minusOne, out);
////	timer.Stop();
////	cout << "index min lento " << index2 << endl;
////
////}
//
