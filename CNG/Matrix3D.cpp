#include "stdafx.h"
#include "Matrix3D.h"

using namespace std;

CMatrix3D::CMatrix3D(void)
{
}


CMatrix3D::~CMatrix3D(void)
{
}

double interp1dData(double xStart, double yStart, double xEnd, double yEnd, double xInterpPoint)
{
	double m;

	if(abs(xEnd - xStart) > 1e-6)
		m = (yEnd - yStart) / (xEnd - xStart);
	else
		m = 0;

	return yStart + m*(xInterpPoint - xStart);
}

//questo richiede che il vettore in ingresso sia monotono crescente.
//da verificare che value stia internamente al range di aVector
void CalcBracketingIndexInVector(vector<double> aVector, double value, int & startIndex, int & endIndex)
{
	startIndex = aVector.size()-1;
	endIndex = 0;

	if(aVector[0] >= value)
	{
		startIndex = 0;
		endIndex = 0;
		return;
	}

	if(aVector[aVector.size()-1] <= value)
	{
		startIndex = aVector.size()-1;
		endIndex = aVector.size()-1;
		return;
	}

	for (size_t i=0; i<aVector.size(); i++ )
	{
		if(aVector[i] > value)
		{
			endIndex = i;
			startIndex = i-1;
			break;
		}
	}
}

int CalculateIndexInsideMatrixStoredAsFlatVector(bool isRowMajor, int xIndex, int yIndex, int xSize, int ySize)
{
	if(isRowMajor)
	{
		return yIndex*xSize + xIndex;
	}
	else
	{
		return xIndex*ySize + yIndex;
	}
}

//attenzione, l'uso di questa funzione prevede che i breakpoints di x e y siano monotoni crescenti
double CMatrix3D::Interp3(vector<vector<double>> & matrix3D, vector<double> depthVector, double interpPointX, double interpPointY, double interpPointZ, vector<double> & xBreakPoints, vector<double> & yBreakPoints, bool isRowMajorOrder)
{
	//per prima  cosa ricerco le due matrici 2d che abbracciano il valore di interpPointZ passato, che rappresenta la profondità del cubo
	int startDepthIndex, endDepthIndex;
	CalcBracketingIndexInVector(depthVector, interpPointZ, startDepthIndex, endDepthIndex);
	double startDepth = depthVector[startDepthIndex];
	double endDepth = depthVector[endDepthIndex];

	//trovati gli indici , mi prendo una ref alle 2 matrici 2d che abbracciano la coordinata Z che esprime la profondità del cubo, attenzione al row/column order wise

	vector<double> & matrix2dBracket1 = matrix3D[startDepthIndex];
	vector<double> & matrix2dBracket2 = matrix3D[endDepthIndex];

	//calcolo gli indici relativi ai punti che abbracciano i punti interpolanti per X e Y
	int startXIndex, endXIndex;
	CalcBracketingIndexInVector(xBreakPoints, interpPointX, startXIndex, endXIndex);

	int startYIndex, endYIndex;
	CalcBracketingIndexInVector(yBreakPoints, interpPointY, startYIndex, endYIndex);

	//ricavo le coordinate che rappresentano i punti di lavoro per le interpolazioni successive
	double x1,x2,y1,y2;

	x1 = xBreakPoints[startXIndex];
	x2 = xBreakPoints[endXIndex];
	y1 = yBreakPoints[startYIndex];
	y2 = yBreakPoints[endYIndex];

	//a questo punto posso iniziare a fare le 7 interpolazioni 1d che realizzano insieme la trilinear interpolation
	// esse sono rappresentate da f1,f2,f3 per la matrice relativa al range inferiore, f4,f5,f6 per quella superiore. 
	// f7 è l'interpolazione fra i risultati parziali, fatta sulla profondità del cubo
	// i valori da recuperare nelle matrici 2d possono essere recuperati sia se le matrici sono memorizzate in modalità "rowMajor" che in modalità "columnMajor"
	double f1,f2,f3,f4,f5,f6,f7;
	
	double z11_1, z12_1, z21_1,z22_1;
	
	int currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,startXIndex,startYIndex,xBreakPoints.size(), yBreakPoints.size());
	z11_1 = matrix2dBracket1[currentIndex];
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,endXIndex,startYIndex,xBreakPoints.size(), yBreakPoints.size());
	z21_1 = matrix2dBracket1[currentIndex];
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,startXIndex,endYIndex,xBreakPoints.size(), yBreakPoints.size());
	z12_1 = matrix2dBracket1[currentIndex];
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,endXIndex,endYIndex,xBreakPoints.size(), yBreakPoints.size());
	z22_1 = matrix2dBracket1[currentIndex];

	double z11_2, z12_2, z21_2,z22_2;
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,startXIndex,startYIndex,xBreakPoints.size(), yBreakPoints.size());
	z11_2 = matrix2dBracket2[currentIndex];
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,endXIndex,startYIndex,xBreakPoints.size(), yBreakPoints.size());
	z21_2 = matrix2dBracket2[currentIndex];
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,startXIndex,endYIndex,xBreakPoints.size(), yBreakPoints.size());
	z12_2 = matrix2dBracket2[currentIndex];
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,endXIndex,endYIndex,xBreakPoints.size(), yBreakPoints.size());
	z22_2 = matrix2dBracket2[currentIndex];

	f1 = interp1dData(x1,z11_1,x2,z21_1,interpPointX);
	f2 = interp1dData(x1,z12_1,x2,z22_1,interpPointX);
	f3 = interp1dData(y1,f1,y2,f2,interpPointY);

	f4 = interp1dData(x1,z11_2,x2,z21_2,interpPointX);
	f5 = interp1dData(x1,z12_2,x2,z22_2,interpPointX);
	f6 = interp1dData(y1,f4,y2,f5,interpPointY);

	f7 = interp1dData(startDepth, f3, endDepth, f6, interpPointZ);

	return f7;
}
