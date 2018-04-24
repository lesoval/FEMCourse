/*
*  ShapeQuad.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "ShapeQuad.h"
#include "tpanic.h"

void ShapeQuad::Shape(VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi)
{

	int nshape = NShapeFunctions(orders);

	//Cálculo das ordens das funções
	for (int i = 0; i < 4; i++)
	{
		orders[i] = 2;
	}

	if (nshape > 4)
	{
		for (int i = 4; i < 8; i++)
		{
			orders[i] = 3;
		}
		orders[8] = 4;
	}

	phi.resize(nshape);
	dphi.Resize(2, nshape);

	//Definição das fuções interpoladoras e suas 1ªs derivadas
	switch (nshape)
	{
	case 4:
		phi[0] = (1 - xi[0])*(1 - xi[1]) / 4;
		phi[1] = (1 + xi[0])*(1 - xi[1]) / 4;
		phi[2] = (1 + xi[0])*(1 + xi[1]) / 4;
		phi[3] = (1 - xi[0])*(1 + xi[1]) / 4;

		dphi(0, 0) = (xi[1] - 1) / 4;	dphi(1, 0) = (xi[0] - 1) / 4;	
		dphi(0, 1) = (1 - xi[1]) / 4;	dphi(1, 1) = (1 - xi[0]) / 4;
		dphi(0, 2) = (xi[1] + 1) / 4;	dphi(1, 2) = (xi[0] + 1) / 4;
		dphi(0, 3) = (1 - xi[1]) / 4;	dphi(1, 3) = (1 - xi[0]) / 4;
		break;
	case 9:
		phi[0] = (pow(xi[0], 2) - xi[0])*(pow(xi[1], 2) - xi[1]) / 4;
		phi[1] = (pow(xi[0], 2) + xi[0])*(pow(xi[1], 2) - xi[1]) / 4;
		phi[2] = (pow(xi[0], 2) + xi[0])*(pow(xi[1], 2) + xi[1]) / 4;
		phi[3] = (pow(xi[0], 2) - xi[0])*(pow(xi[1], 2) + xi[1]) / 4;
		phi[4] = (1 - pow(xi[0], 2))*(pow(xi[1], 2) - xi[1]) / 2;
		phi[5] = (pow(xi[0], 2) + xi[0])*(1 - pow(xi[1], 2)) / 2;
		phi[6] = (1 - pow(xi[0], 2))*(pow(xi[1], 2) + xi[1]) / 2;
		phi[7] = (pow(xi[0], 2) - xi[0])*(1 - pow(xi[1], 2)) / 2;
		phi[8] = (1 - pow(xi[1], 2))*(1 - pow(xi[0], 2)) / 4;

		dphi(0, 0) = -(-1 + xi[1])*(2 * xi[0] + xi[1]) / 4;		dphi(1, 0) = -(1 + xi[0])*(xi[0] - 2 * xi[1]) / 4;
		dphi(0, 1) = -(2 * xi[0] - xi[1])*(-1 + xi[1]) / 4;		dphi(1, 1) = -(-1 + xi[0])*(xi[0] + 2 * xi[1]) / 4;
		dphi(0, 2) = (1 + xi[1])*(2 * xi[0] + xi[1]) / 4;		dphi(1, 2) = (1 + xi[0])*(xi[0] + 2 * xi[1]) / 4;
		dphi(0, 3) = (2 * xi[0] - xi[1])*(1 + xi[1]) / 4;		dphi(1, 3) = (-1 + xi[0])*(xi[0] - 2 * xi[1]) / 4;
		dphi(0, 4) = xi[0] * (-1 + xi[1]);						dphi(1, 4) = (-1 + pow(xi[0],2)) / 2;
		dphi(0, 5) = (-1 + pow(xi[1], 2)) / 2;					dphi(1, 5) = -(1 + xi[0])*xi[1];
		dphi(0, 6) = -xi[0] * (1 + xi[1]);						dphi(1, 6) = (1 - pow(xi[0], 2)) / 2;
		dphi(0, 7) = (-1 + pow(xi[1], 2)) / 2;					dphi(1, 7) = (-1 + xi[0])*xi[1];
		dphi(0, 8) = xi[0] * (-1 + pow(xi[1], 2)) / 2;			dphi(1, 8) = (-1 + pow(xi[0], 2)) *xi[1] / 2;
		break;
	default:
		DebugStop();
		break;
	}
}

int ShapeQuad::NShapeFunctions(int side, VecInt &orders)
{
	int nsides = orders.size();
	int nshape;

	if (nsides<4 || nsides>9 || side>nsides)
	{
		DebugStop();
	}

	//Cálculo das ordens das funções
	for (int i = 0; i < 4; i++)
	{
		orders[i] = 2;
	}

	if (nsides>4)
	{
		for (int i = 4; i < 8; i++)
		{
			orders[i] = 3;
		}
		orders[8] = 4;
	}
	
	if (side<4)
	{
		nshape = 1;
	}

	if (side<8)
	{
		nshape = orders[side] - 1;
	}

	if (side==8)
	{
		nshape = pow(orders[side] - 1, 2);
	}

	return nshape;
}

int ShapeQuad::NShapeFunctions(VecInt &orders)
{
	if (orders.size()<4|| orders.size()>9)
	{
		DebugStop();
	}

	return orders.size();
}