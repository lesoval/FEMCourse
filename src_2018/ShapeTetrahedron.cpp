/*
*  ShapeTetrahedron.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "ShapeTetrahedron.h"
#include "tpanic.h"

void ShapeTetrahedron::Shape(VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi)
{

	int nshape = NShapeFunctions(orders);

	//Cálculo das ordens das funções
	switch (nshape)
	{
	case 4:
		for (int i = 0; i < nshape; i++)
		{
			orders[i] = 1;
		}
		break;
	case 10:

		break;
	case 15:

		break;
	}

	phi.resize(nshape);
	dphi.Resize(3, nshape);

	//Definição das fuções interpoladoras e suas 1ªs derivadas
	switch (nshape)
	{
	case 4:
		phi[0] = 1 - xi[0] - xi[1] - xi[2];
		phi[1] = xi[0];
		phi[2] = xi[1];
		phi[3] = xi[2];

		dphi(0, 0) = -1.0;	dphi(1, 0) = -1.0;	dphi(2, 0) = -1.0;
		dphi(0, 1) = 1.0;	dphi(1, 1) = 0.0;	dphi(2, 1) = 0.0;
		dphi(0, 2) = 0.0;	dphi(1, 2) = 1.0;	dphi(2, 2) = 0.0;
		dphi(0, 3) = 0.0;	dphi(1, 3) = 0.0;	dphi(2, 3) = 1.0;
		break;
	case 10:
		
		break;
	case 15:
		
		break;
	default:
		DebugStop();
		break;
	}
}

int ShapeTetrahedron::NShapeFunctions(int side, VecInt &orders)
{
	int nsides = orders.size();
	int nshape;

	if (nsides<4 || nsides>15 || side>nsides)
	{
		DebugStop();
	}

	//Cálculo das ordens das funções
	switch (nsides)
	{
	case 4:
		for (int i = 0; i < nsides; i++)
		{
			orders[i] = 1;
		}
		break;
	case 10:

		break;
	case 15:

		break;
	}

	if (side < 4)
	{
		nshape = 1;
	}

	if (side < 10)
	{
		nshape = orders[side] - 1;
	}

	if (side < 14)
	{
		int sum = 0;
		for (int i = 0; i < orders[side] - 1; i++)
		{
			sum += i;
			nshape = sum;
		}
	}

	if (side == 14) 
	{
		int totsum = 0, sum;
		for (int i = 1; i<orders[side] - 2; i++) 
		{
			sum = i * (i + 1) / 2;
			totsum += sum;
			nshape = totsum;
		}
	}

	return nshape;
}

int ShapeTetrahedron::NShapeFunctions(VecInt &orders)
{
	if (orders.size()<4 || orders.size()>15)
	{
		DebugStop();
	}

	return orders.size();
}