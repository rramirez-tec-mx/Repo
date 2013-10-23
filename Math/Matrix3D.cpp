//#include "stdafx.h"
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
void CalcBracketingIndexInVector(const vector<double> & aVector, double value, size_t & startIndex, size_t & endIndex)
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
double CMatrix3D::Interp3(const vector<vector<double>> & matrix3D, const vector<double> & depthVector, double interpPointX, double interpPointY, double interpPointZ, const vector<double> & xBreakPoints, const vector<double> & yBreakPoints, bool isRowMajorOrder)
{
	//per prima  cosa ricerco le due matrici 2d che abbracciano il valore di interpPointZ passato, che rappresenta la profondità del cubo
	size_t startDepthIndex, endDepthIndex;
	CalcBracketingIndexInVector(depthVector, interpPointZ, startDepthIndex, endDepthIndex);
	double startDepth = depthVector[startDepthIndex];
	double endDepth = depthVector[endDepthIndex];

	//trovati gli indici , mi prendo una ref alle 2 matrici 2d che abbracciano la coordinata Z che esprime la profondità del cubo, attenzione al row/column order wise

	const vector<double> & matrix2dBracket1 = matrix3D[startDepthIndex];
	const vector<double> & matrix2dBracket2 = matrix3D[endDepthIndex];

	//calcolo gli indici relativi ai punti che abbracciano i punti interpolanti per X e Y
	size_t startXIndex, endXIndex;
	CalcBracketingIndexInVector(xBreakPoints, interpPointX, startXIndex, endXIndex);

	size_t startYIndex, endYIndex;
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
	double z11_2, z12_2, z21_2, z22_2;
	
	int currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,startXIndex,startYIndex,xBreakPoints.size(), yBreakPoints.size());
	z11_1 = matrix2dBracket1[currentIndex];
	z11_2 = matrix2dBracket2[currentIndex];
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,endXIndex,startYIndex,xBreakPoints.size(), yBreakPoints.size());
	z21_1 = matrix2dBracket1[currentIndex];
	z21_2 = matrix2dBracket2[currentIndex];
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,startXIndex,endYIndex,xBreakPoints.size(), yBreakPoints.size());
	z12_1 = matrix2dBracket1[currentIndex];
	z12_2 = matrix2dBracket2[currentIndex];
	currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder,endXIndex,endYIndex,xBreakPoints.size(), yBreakPoints.size());
	z22_1 = matrix2dBracket1[currentIndex];
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


void Find2DMatricesOfBracketing(const vector<double> & depthVector, size_t & startDepthIndex, size_t & endDepthIndex, double interpPointZ, double & startDepth, double & endDepth)
{
	CalcBracketingIndexInVector(depthVector, interpPointZ, startDepthIndex, endDepthIndex);
	startDepth = depthVector[startDepthIndex];
	endDepth = depthVector[endDepthIndex];
}



double inverseInXOrY_internal(char dimensionToInverte, bool isRowMajorOrder, double indipendentInterpPoint, double dipendentInterpPoint, double interpPointDepth,  const vector<double> & indipVectorBkp, const vector<double> & dipVectorBkp, size_t XSize, size_t YSize, const vector<double> & matrix2dBracket1, const vector<double> & matrix2dBracket2, double startDepth, double endDepth)
{
	if(dimensionToInverte=='y' || dimensionToInverte=='x')
	{				
		size_t startIndipIndex, endIndipIndex;
		CalcBracketingIndexInVector(indipVectorBkp, indipendentInterpPoint, startIndipIndex, endIndipIndex);

		size_t startDipIndex, endDipIndex;
		vector<double> lowerBoundVector1;
		vector<double> upperBoundVector1;
		vector<double> lowerBoundVector2;
		vector<double> upperBoundVector2;		
		size_t dipVecSize = dipVectorBkp.size();
		lowerBoundVector1.resize(dipVecSize);
		upperBoundVector1.resize(dipVecSize);
		lowerBoundVector2.resize(dipVecSize);
		upperBoundVector2.resize(dipVecSize);

		for(size_t k=0; k<dipVecSize; k++)
		{
			size_t currentIndex;

			if(dimensionToInverte=='y')
				currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, startIndipIndex, k, XSize, YSize);
			else
				currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, k, startIndipIndex, XSize, YSize);

			lowerBoundVector1[k] = matrix2dBracket1[currentIndex];
			lowerBoundVector2[k] = matrix2dBracket2[currentIndex];

			if(dimensionToInverte=='y')
				currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, endIndipIndex, k, XSize, YSize);
			else
				currentIndex = CalculateIndexInsideMatrixStoredAsFlatVector(isRowMajorOrder, k, endIndipIndex, XSize, YSize);

			upperBoundVector1[k] = matrix2dBracket1[currentIndex];
			upperBoundVector2[k] = matrix2dBracket2[currentIndex];
		}

		vector<double> interpolantVector1, interpolantVector2, interpolantVectorResult;
		interpolantVector1.resize(dipVecSize);
		interpolantVector2.resize(dipVecSize);
		interpolantVectorResult.resize(dipVecSize);
		double indipValue1, indipValue2;
		indipValue1 = indipVectorBkp[startIndipIndex];
		indipValue2 = indipVectorBkp[endIndipIndex];

		//parallel_for (size_t(0), ySize, [&](size_t k)
		for (size_t k=0; k< dipVecSize; k++)
		{
			interpolantVector1[k] = interp1dData(indipValue1, lowerBoundVector1[k], indipValue2, upperBoundVector1[k], indipendentInterpPoint);
			interpolantVector2[k] = interp1dData(indipValue1, lowerBoundVector2[k], indipValue2, upperBoundVector2[k], indipendentInterpPoint);
		}
		//});

		for (size_t k=0; k< dipVecSize; k++)
		{
			interpolantVectorResult[k] = interp1dData(startDepth, interpolantVector1[k], endDepth, interpolantVector2[k], interpPointDepth);
		}

		CalcBracketingIndexInVector(interpolantVectorResult, dipendentInterpPoint, startDipIndex, endDipIndex);
	
		// infine l'ultima interpolazione fra i risultati parziali ottenuti in f3 e f6
		double f7;
		f7 = interp1dData(interpolantVectorResult[startDipIndex], dipVectorBkp[startDipIndex], interpolantVectorResult[endDipIndex], dipVectorBkp[endDipIndex], dipendentInterpPoint);

		return f7;
	}	

	return 0;
}



double CMatrix3D::Interp3Inverse(const vector<vector<double>> & matrix3D, const vector<double> & depthVector, double interpPointX, double interpPointY, double interpPointZ, const vector<double> & xBreakPoints, const vector<double> & yBreakPoints, const char dimensionToInverte, bool isRowMajorOrder)
{

	double f7 = 0.0;		

	if(dimensionToInverte=='y' || dimensionToInverte=='x')
	{		
		double startDepth;
		double endDepth;
		size_t startDepthIndex, endDepthIndex;
		Find2DMatricesOfBracketing(depthVector, startDepthIndex, endDepthIndex, interpPointZ, startDepth, endDepth);

		const vector<double> & matrix2dBracket1 = matrix3D[startDepthIndex];
		const vector<double> & matrix2dBracket2 = matrix3D[endDepthIndex];
			
		if(dimensionToInverte=='y')
		{										
			f7 = inverseInXOrY_internal('y', isRowMajorOrder, interpPointX, interpPointY, interpPointZ, xBreakPoints, yBreakPoints, xBreakPoints.size(), yBreakPoints.size(), matrix2dBracket1, matrix2dBracket2, startDepth, endDepth);			
		}
		else
		if(dimensionToInverte=='x')
		{										
			f7 = inverseInXOrY_internal('x', isRowMajorOrder, interpPointY, interpPointX, interpPointZ, yBreakPoints, xBreakPoints, xBreakPoints.size(), yBreakPoints.size(), matrix2dBracket1, matrix2dBracket2, startDepth, endDepth);			
		}
	}
	else
	if(dimensionToInverte=='z')
	{
		size_t startXIndex, endXIndex;
		size_t startYIndex, endYIndex;
		size_t startZIndex, endZIndex;
		double x1,x2,y1,y2;
		double z11_1, z12_1, z21_1,z22_1;
		double f1, f2, f3;
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
			const vector<double> & current2dMatrix = matrix3D[k];
			
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
	}

	return f7;
}
