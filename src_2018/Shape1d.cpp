/*
*  Shape1d.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

//#include "Topology1d.h"
#include "Shape1d.h"
#include "tpanic.h"

void Shape1d::Shape(VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi)
{
	int nshape = NShapeFunctions(orders);

	phi.resize(nshape);
	dphi.Resize(1, nshape);

	for (int i = 0; i < nshape; i++)
	{
		orders[i] = nshape - 1;//Definição da ordem das funçoes interpoladoras
		phi[i] = 1;
		dphi(0, i) = 0;
	}

	//Cálculo das coordenadas paramétricas dos lados externos
	VecDouble co(nshape);
	co[0] = -1;
	co[1] = 1;
	//Cálculo das coordenadas paramétricas dos lados internos
	if (nshape>2)
	{
		double order = nshape - 1;
		for (int i = 2; i < nshape; i++)
		{
			co[i] = -1 + (i - 1) * 2 / order;
		}
	}
	
	//Definição da fução interpoladora e sua 1ª derivada
	for (int i = 0; i < nshape; i++)
	{
		for (int j = 0; j < nshape; j++)
		{
			if (i != j)
			{
				phi[i] *= (xi[0] - co[j]) / (co[i] - co[j]);

				TMatrix dphi_(1, nshape);
				dphi_(0, i) = 1 / (co[i] - co[j]);

				for (int k = 0; k < nshape; k++)
				{
					if (k != i && k != j)
					{
						dphi_(0, i) *= (xi[0] - co[k]) / (co[i] - co[k]);
					}

				}

				dphi(0, i) += dphi_(0, i);

			}

		}
	}
}

int Shape1d::NShapeFunctions(int side, VecInt &orders)
{
	int nsides = orders.size();
	int order = nsides - 1;
	int nshape;

	if (nsides<2||side>nsides)
	{
		DebugStop();
	}

	for (int i = 0; i < nsides; i++)
	{
		orders[i] = order;
	}

	if (side<2)
	{
		nshape = 1;
	}
	else
	{
		nshape = orders[side] - 1;
	}

	return nshape;
}

int Shape1d::NShapeFunctions(VecInt &orders)
{
	if (orders.size()<2)
	{
		DebugStop();
	}

	return orders.size();
}