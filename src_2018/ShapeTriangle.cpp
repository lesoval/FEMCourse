/*
*  ShapeTriangle.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "ShapeTriangle.h"
#include "tpanic.h"

void ShapeTriangle::Shape(VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi)
{

	int nshape = NShapeFunctions(orders);

	//Cálculo das ordens das funções
	switch (nshape)
	{
	case 3:
		for (int i = 0; i < nshape; i++)
		{
			orders[i] = 1;
		}
		break;
	case 6:
		for (int i = 0; i < nshape; i++)
		{
			orders[i] = 2;
		}
	case 10:
		for (int i = 0; i < nshape; i++)
		{
			orders[i] = 3;
		}
		break;
	}

	phi.resize(nshape);
	dphi.Resize(2, nshape);

	//Definição das fuções interpoladoras e suas 1ªs derivadas
	switch (nshape)
	{
	case 3:
		phi[0] = 1 - xi[0] - xi[1];
		phi[1] = xi[0];
		phi[2] = xi[1];

		dphi(0, 0) = -1;	dphi(1, 0) = -1;
		dphi(0, 1) = 1;		dphi(1, 1) = 0;
		dphi(0, 2) = 0;		dphi(1, 2) = 1;
		break;
	case 6:
		phi[0] = 2 * (1 - xi[0] - xi[1]) * ((1 - xi[0] - xi[1]) - 0.5);
		phi[1] = 2 * xi[0] * (xi[0] - 0.5);
		phi[2] = 2 * xi[1] * (xi[1] - 0.5);
		phi[3] = 4 * (1 - xi[0] - xi[1]) * xi[0];
		phi[4] = 4 * xi[0] * xi[1];
		phi[5] = 4 * xi[1] * (1 - xi[0] - xi[1]);

		dphi(0, 0) = -2 * (0.5 - xi[1] - xi[0]) - 2 * (1 - xi[1] - xi[0]);		dphi(1, 0) = -2 * (0.5 - xi[1] - xi[0]) - 2 * (1 - xi[1] - xi[0]);
		dphi(0, 1) = 2 * (-0.5 + xi[0]) + 2 * xi[0];							dphi(1, 1) = 0;
		dphi(0, 2) = 0;															dphi(1, 2) = 2 * (-0.5 + xi[1]) + 2 * xi[1];
		dphi(0, 3) = 4 * (1 - xi[1] - xi[0]) - 4 * xi[0];						dphi(1, 3) = -4 * xi[0];
		dphi(0, 4) = 4 * xi[1];													dphi(1, 4) = 4 * xi[0];
		dphi(0, 5) = -4 * xi[1];												dphi(1, 5) = -4 * xi[1] + 4 * (1 - xi[1] - xi[0]);
		break;
	case 10:
		phi[0] = (9 / 2)*(1 - xi[0] - xi[1]) * ((1 - xi[0] - xi[1]) - 2 / 3)*((1 - xi[0] - xi[1]) - 1 / 3);
		phi[1] = (9 / 2)*xi[0] * (xi[0] - 2 / 3)*(xi[0] - 1 / 3);
		phi[2] = (9 / 2)*xi[1] * (xi[1] - 2 / 3)*(xi[1] - 1 / 3);
		phi[3] = (27 / 2)*(1 - xi[0] - xi[1]) * xi[0] * ((1 - xi[0] - xi[1]) - 1 / 3);
		phi[4] = (27 / 2)*(1 - xi[0] - xi[1]) * xi[0] * (xi[0] - 1 / 3);
		phi[5] = (27 / 2)*xi[0] * xi[1] * (xi[0] - 1 / 3);
		phi[6] = (27 / 2)*xi[0] * xi[1] * (xi[0] - 2 / 3);
		phi[7] = (27 / 2)*(1 - xi[0] - xi[1]) * xi[1] * (xi[1] - 1 / 3);
		phi[8] = (27 / 2)*(1 - xi[0] - xi[1]) * xi[1] * ((1 - xi[0] - xi[1]) - 1 / 3);
		phi[9] = 27 * (1 - xi[0] - xi[1]) * xi[0] * xi[1];

		dphi(0, 0) = -(9 / 2)*(1 / 3 - xi[0] - xi[1])*(2 / 3 - xi[0] - xi[1]) -
			(9 / 2)*(1 / 3 - xi[0] - xi[1])*(1 - xi[0] - xi[1]) -
			(9 / 2)*(2 / 3 - xi[0] - xi[1])*(1 - xi[0] - xi[1]);
		dphi(0, 1) = (9 / 2)*(-(2 / 3) + xi[0])*(-(1 / 3) + xi[0]) +
			(9 / 2)*(-(2 / 3) + xi[0])*xi[0] + (9 / 2)*(-(1 / 3) + xi[0])*xi[0];
		dphi(0, 2) = 0;
		dphi(0, 3) = -(27 / 2)*xi[0] * (2 / 3 - xi[0] - xi[1]) -
			(27 / 2)*xi[0] * (1 - xi[0] - xi[1]) +
			(27 / 2)*(2 / 3 - xi[0] - xi[1])*(1 - xi[0] - xi[1]);
		dphi(0, 4) = -(27 / 2)*(-(1 / 3) + xi[0])*xi[0] +
			(27 / 2)*(-(1 / 3) + xi[0])*(1 - xi[0] - xi[1]) +
			(27 / 2)*xi[0] * (1 - xi[0] - xi[1]);
		dphi(0, 5) = (27 / 2)*(-(1 / 3) + xi[0])*xi[1] + (27 / 2)*xi[0] * xi[1];
		dphi(0, 6) = (27 / 2)*(-(2 / 3) + xi[0])*xi[1] + (27 / 2)*xi[0] * xi[1];
		dphi(0, 7) = -(27 / 2)*(-(1 / 3) + xi[1])*xi[1];
		dphi(0, 8) = -(27 / 2)*(2 / 3 - xi[0] - xi[1])*xi[1] -
			(27 / 2)*(1 - xi[0] - xi[1])*xi[1];
		dphi(0, 9) = -27 * xi[0] * xi[1] + 27 * (1 - xi[0] - xi[1])*xi[1];

		dphi(1, 0) = -(9 / 2)*(1 / 3 - xi[0] - xi[1])*(2 / 3 - xi[0] - xi[1]) -
			(9 / 2)*(1 / 3 - xi[0] - xi[1])*(1 - xi[0] - xi[1]) -
			(9 / 2)*(2 / 3 - xi[0] - xi[1])*(1 - xi[0] - xi[1]);
		dphi(1, 1) = 0;
		dphi(1, 2) = (9 / 2)*(-(2 / 3) + xi[1])*(-(1 / 3) + xi[1]) +
			(9 / 2)*(-(2 / 3) + xi[1])*xi[1] + (9 / 2)*(-(1 / 3) + xi[1])*xi[1];
		dphi(1, 3) = -(27 / 2)*xi[0] * (2 / 3 - xi[0] - xi[1]) -
			(27 / 2)*xi[0] * (1 - xi[0] - xi[1]);
		dphi(1, 4) = -(27 / 2)*(-(1 / 3) + xi[0])*xi[0];
		dphi(1, 5) = (27 / 2)*(-(1 / 3) + xi[0])*xi[0];
		dphi(1, 6) = (27 / 2)*(-(2 / 3) + xi[0])*xi[0];
		dphi(1, 7) = (27 / 2)*(1 - xi[0] - xi[1])*(-(1 / 3) + xi[1]) +
			(27 / 2)*(1 - xi[0] - xi[1])*xi[1] -
			(27 / 2)*(-(1 / 3) + xi[1])*xi[1];
		dphi(1, 8) = (27 / 2)*(2 / 3 - xi[0] - xi[1])*(1 - xi[0] - xi[1]) -
			(27 / 2)*(2 / 3 - xi[0] - xi[1])*xi[1] -
			(27 / 2)*(1 - xi[0] - xi[1])*xi[1];
		dphi(1, 9) = 27 * xi[0] * (1 - xi[0] - xi[1]) - 27 * xi[0] * xi[1];
		break;
	default:
		DebugStop();
		break;
	}
}

int ShapeTriangle::NShapeFunctions(int side, VecInt &orders)
{
	int nsides = orders.size();
	int nshape;

	if (nsides<3 || nsides>10 || side>nsides)
	{
		DebugStop();
	}

	//Cálculo das ordens das funções
	switch (nsides)
	{
	case 3:
		for (int i = 0; i < nsides; i++)
		{
			orders[i] = 1;
		}
		break;
	case 6:
		for (int i = 0; i < nsides; i++)
		{
			orders[i] = 2;
		}
	case 10:
		for (int i = 0; i < nsides; i++)
		{
			orders[i] = 3;
		}
		break;
	}
	
	if (side<3)
	{
		nshape = 1;
	}

	else
	{
		nshape = orders[side] - 1;
	}

	return nshape;
}

int ShapeTriangle::NShapeFunctions(VecInt &orders)
{
	if (orders.size()<3 || orders.size()>10)
	{
		DebugStop();
	}

	return orders.size();
}