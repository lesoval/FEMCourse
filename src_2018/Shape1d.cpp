/*
*  Shape1d.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "Shape1d.h"
#include "tpanic.h"

void Shape1d::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi)
{
	if (xi[0]<-1 || xi[0]>1)
	{
		std::cout << "Shape1d::Shape --> Invalid coordinate 'xi'" << std::endl;
		DebugStop();
	}

	int nShapes = NShapeFunctions(orders);
	double order = nShapes - 1;

	phi.resize(nShapes);
	dphi.Resize(1, nShapes);

	if (order==0)
	{
		phi[0] = 1;
		dphi(0, 0) = 0;
	}

	else
	{
		//Coordenadas paramétricas das extremidades
		VecDouble co(nShapes);
		co[0] = -1;
		co[1] = 1;

		//Coordenadas paramétricas dos pontos internos
		for (int i = nCorners; i < nShapes; i++)
		{
			co[i] = -1 + (i - 1) * 2 / order;
		}

		//Retorna os valores de phi e dphi para o ponto xi
		double ksi = xi[0];

		for (int i = 0; i < nShapes; i++)
		{
			phi[i] = 1;
			dphi(0, i) = 0;
		}

		for (int i = 0; i < nShapes; i++)
		{
			for (int j = 0; j < nShapes; j++)
			{
				if (i != j)
				{
					phi[i] *= (ksi - co[j]) / (co[i] - co[j]);

					TMatrix dphi_(1, nShapes);
					dphi_(0, i) = 1 / (co[i] - co[j]);

					for (int k = 0; k < nShapes; k++)
					{
						if (k != i && k != j)
						{
							dphi_(0, i) *= (ksi - co[k]) / (co[i] - co[k]);
						}

					}

					dphi(0, i) += dphi_(0, i);

				}

			}
		}
	}
}

int Shape1d::NShapeFunctions(int side, int order)
{
	if (order<0)
	{
		std::cout << "Shape1d::NShapeFunctions --> Invalid shape function order" << std::endl;
		DebugStop();
	}

	switch (side)
	{
	case 0:
	case 1:
		return 1;
		break;
	case 2:
		return order - 1;
		break;
	default:
		std::cout << "Shape1d::NShapeFunctions --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

int Shape1d::NShapeFunctions(VecInt &orders)
{
	if (orders.size() != nSides)
	{
		std::cout << "Shape1d::NShapeFunctions --> Invalid dimention for 'orders' vector" << std::endl;
		DebugStop();
	}

	int nShapes = nCorners;

	for (int i = nCorners; i < nSides; i++)
	{
		nShapes += NShapeFunctions(i, orders[i - nCorners]);
	}

	return nShapes;
}