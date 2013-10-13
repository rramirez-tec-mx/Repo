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


double CMatrix3D::Interp3Inverse(vector<vector<double>> & matrix3D, vector<double> depthVector, double interpPointX, double interpPointY, double interpPointZ, vector<double> & xBreakPoints, vector<double> & yBreakPoints, const char dimensionToInverte, bool isRowMajorOrder)
{

	//per ora assumiamo che le matrici 2d siano state storate column wise, per cui ricavare le colonne di bracketing è un banale memcpy, mentre
	// ricavare le righe di bracketing impone un ciclo

	if(dimensionToInverte=='y')
	{
		int startDepthIndex, endDepthIndex;
		CalcBracketingIndexInVector(depthVector, interpPointZ, startDepthIndex, endDepthIndex);
		double startDepth = depthVector[startDepthIndex];
		double endDepth = depthVector[endDepthIndex];
		vector<double> & matrix2dBracket1 = matrix3D[startDepthIndex];
		vector<double> & matrix2dBracket2 = matrix3D[endDepthIndex];
		//calcolo gli indici relativi ai punti che abbracciano i punti interpolanti per X e Y
		int startXIndex, endXIndex;
		CalcBracketingIndexInVector(xBreakPoints, interpPointX, startXIndex, endXIndex);

		int startYIndex, endYIndex;
		vector<double> lowerBoundColumnVector1;
		vector<double> upperBoundColumnVector1;
		vector<double> lowerBoundColumnVector2;
		vector<double> upperBoundColumnVector2;
		size_t xSize = xBreakPoints.size();
		size_t ySize = yBreakPoints.size();
		lowerBoundColumnVector1.resize(ySize);
		upperBoundColumnVector1.resize(ySize);
		lowerBoundColumnVector2.resize(ySize);
		upperBoundColumnVector2.resize(ySize);

		for(size_t k=0; k<ySize; k++)
		{
			size_t currentIndex;
			currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, startXIndex, k, xSize, ySize);
			lowerBoundColumnVector1[k] = matrix2dBracket1[currentIndex];
			lowerBoundColumnVector2[k] = matrix2dBracket2[currentIndex];

			currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, endXIndex, k, xSize, ySize);
			upperBoundColumnVector1[k] = matrix2dBracket1[currentIndex];
			upperBoundColumnVector2[k] = matrix2dBracket2[currentIndex];
		}

		vector<double> interpolantVector1, interpolantVector2, interpolantVectorResult;
		interpolantVector1.resize(ySize);
		interpolantVector2.resize(ySize);
		interpolantVectorResult.resize(ySize);
		double x1,x2;
		x1 = xBreakPoints[startXIndex];
		x2 = xBreakPoints[endXIndex];

		//parallel_for (size_t(0), ySize, [&](size_t k)
		for (size_t k=0; k< ySize; k++)
		{
			interpolantVector1[k] = interp1dData(x1, lowerBoundColumnVector1[k], x2, upperBoundColumnVector1[k], interpPointX);
			interpolantVector2[k] = interp1dData(x1, lowerBoundColumnVector2[k], x2, upperBoundColumnVector2[k], interpPointX);
		}
		//});

		for (size_t k=0; k< ySize; k++)
		{
			interpolantVectorResult[k] = interp1dData(startDepth, interpolantVector1[k], endDepth, interpolantVector2[k], interpPointZ);
		}

		CalcBracketingIndexInVector(interpolantVectorResult, interpPointY, startYIndex, endYIndex);
	
		// infine l'ultima interpolazione fra i risultati parziali ottenuti in f3 e f6
		double f7;
		f7 = interp1dData(interpolantVectorResult[startYIndex], yBreakPoints[startYIndex], interpolantVectorResult[endYIndex], yBreakPoints[endYIndex], interpPointY);

		return f7;
	}
	else
	if(dimensionToInverte=='x')
	{
		int startDepthIndex, endDepthIndex;
		CalcBracketingIndexInVector(depthVector, interpPointZ, startDepthIndex, endDepthIndex);
		double startDepth = depthVector[startDepthIndex];
		double endDepth = depthVector[endDepthIndex];
		vector<double> & matrix2dBracket1 = matrix3D[startDepthIndex];
		vector<double> & matrix2dBracket2 = matrix3D[endDepthIndex];

		int startYIndex, endYIndex;
		CalcBracketingIndexInVector(yBreakPoints, interpPointY, startYIndex, endYIndex);

		int startXIndex, endXIndex;
		vector<double> lowerBoundRowVector1;
		vector<double> upperBoundRowVector1;
		vector<double> lowerBoundRowVector2;
		vector<double> upperBoundRowVector2;
		size_t xSize = xBreakPoints.size();
		size_t ySize = yBreakPoints.size();
		lowerBoundRowVector1.resize(xSize);
		upperBoundRowVector1.resize(xSize);
		lowerBoundRowVector2.resize(xSize);
		upperBoundRowVector2.resize(xSize);
		
		for(size_t k=0; k<xSize; k++)
		{
			size_t currentIndex;
			currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, k, startYIndex, xSize, ySize);
			lowerBoundRowVector1[k] = matrix2dBracket1[currentIndex];
			lowerBoundRowVector2[k] = matrix2dBracket2[currentIndex];

			currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, k, endYIndex, xSize, ySize);
			upperBoundRowVector1[k] = matrix2dBracket1[currentIndex];
			upperBoundRowVector2[k] = matrix2dBracket2[currentIndex];
		}


		vector<double> interpolantVector1, interpolantVector2, interpolantVectorResult;
		interpolantVector1.resize(xSize);
		interpolantVector2.resize(xSize);
		interpolantVectorResult.resize(xSize);
		double y1,y2;
		y1 = yBreakPoints[startYIndex];
		y2 = yBreakPoints[endYIndex];

		//parallel_for (size_t(0), ySize, [&](size_t k)
		for (size_t k=0; k< xSize; k++)
		{
			interpolantVector1[k] = interp1dData(y1, lowerBoundRowVector1[k], y2, upperBoundRowVector1[k], interpPointY);
			interpolantVector2[k] = interp1dData(y1, lowerBoundRowVector2[k], y2, upperBoundRowVector2[k], interpPointY);
		}
		//});

		for (size_t k=0; k< xSize; k++)
		{
			interpolantVectorResult[k] = interp1dData(startDepth, interpolantVector1[k], endDepth, interpolantVector2[k], interpPointZ);
		}

		CalcBracketingIndexInVector(interpolantVectorResult, interpPointX, startXIndex, endXIndex);
	
		// infine l'ultima interpolazione fra i risultati parziali ottenuti in f3 e f6
		double f7;
		f7 = interp1dData(interpolantVectorResult[startXIndex], xBreakPoints[startXIndex], interpolantVectorResult[endXIndex], xBreakPoints[endXIndex], interpPointX);

		return f7;
	}
	else
	if(dimensionToInverte=='z')
	{
		int startXIndex, endXIndex;
		int startYIndex, endYIndex;
		int startZIndex, endZIndex;
		double x1,x2,y1,y2;
		double z11_1, z12_1, z21_1,z22_1;
		double f1, f2, f3, f7;
		vector<double> interpolantVectorResult;
		interpolantVectorResult.resize(depthVector.size());
		size_t xSize = xBreakPoints.size();
		size_t ySize = yBreakPoints.size();
		CalcBracketingIndexInVector(xBreakPoints, interpPointX, startXIndex, endXIndex);
		CalcBracketingIndexInVector(yBreakPoints, interpPointY, startYIndex, endYIndex);
		x1 = xBreakPoints[startXIndex];
		x2 = xBreakPoints[endXIndex];
		y1 = yBreakPoints[startYIndex];
		y2 = yBreakPoints[endYIndex];

		//per tutte le matrici 2d, devo calcolare i punti interpolanti che abbracciano x e y passati, effettuando quindi 3 interpolazioni 1d per ogni matrice 
		for(size_t k=0; k<depthVector.size(); k++)
		{
			size_t currentIndex;
			vector<double> & current2dMatrix = matrix3D[k];
			
			currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, startXIndex, startYIndex, xSize, ySize);
			z11_1 = current2dMatrix[currentIndex];
			currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, endXIndex, startYIndex, xSize, ySize);
			z21_1 = current2dMatrix[currentIndex];
			currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, startXIndex, endYIndex, xSize, ySize);
			z12_1 = current2dMatrix[currentIndex];
			currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, endXIndex, endYIndex, xSize, ySize);
			z22_1 = current2dMatrix[currentIndex];

			f1 = interp1dData(x1, z11_1, x2, z21_1, interpPointX);
			f2 = interp1dData(x1, z12_1, x2, z22_1, interpPointX);
			f3 = interp1dData(y1, f1, y2, f2,interpPointY);
			interpolantVectorResult[k] = f3;	
		}

		CalcBracketingIndexInVector(interpolantVectorResult, interpPointZ, startZIndex, endZIndex);

		f7 = interp1dData(interpolantVectorResult[startZIndex], depthVector[startZIndex], interpolantVectorResult[endZIndex], depthVector[endZIndex], interpPointZ);

		return f7;
	}

	return 0;
}
