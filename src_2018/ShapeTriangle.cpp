/*
*  ShapeTriangle.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "ShapeTriangle.h"
#include "tpanic.h"

void ShapeTriangle::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi)
{
	for (int i = 0; i < Dimension; i++)
	{
		if (xi[i]<0 || xi[i]>1)
		{
			std::cout << "ShapeTriangle::Shape --> Invalid coordinate 'xi[" << i << "]'" << std::endl;
			DebugStop();
		}
	}

	int nShapes = NShapeFunctions(orders);

	phi.resize(nShapes);
	dphi.Resize(2, nShapes);

	//Calcula os valores de phi e dphi para o ponto xi(ksi,eta)
	double ksi = xi[0];
	double eta = xi[1];

	switch (nShapes)
	{
	case 3:
		phi[0] = 1 - ksi - eta;
		phi[1] = ksi;
		phi[2] = eta;

		dphi(0, 0) = -1;	dphi(1, 0) = -1;
		dphi(0, 1) = 1;		dphi(1, 1) = 0;
		dphi(0, 2) = 0;		dphi(1, 2) = 1;
		break;
	case 6:
		phi[0] = -(1 - ksi - eta)*(1 - 2 * (1 - ksi - eta));
		phi[1] = -ksi * (1 - 2 * ksi);
		phi[2] = -eta * (1 - 2 * ksi);
		phi[3] = 4 * ksi*(1 - ksi - eta);
		phi[4] = 4 * ksi*eta;
		phi[5] = 4 * eta*(1 - ksi - eta);

		dphi(0, 0) = 1 - 4 * (1 - ksi - eta);		dphi(1, 0) = 1 - 4 * (1 - ksi - eta);
		dphi(0, 1) = -1 + 4 * ksi;					dphi(1, 1) = 0;
		dphi(0, 2) = 0;								dphi(1, 2) = -1 + 4 * eta;
		dphi(0, 3) = 4 * (1 - 2 * ksi - eta);		dphi(1, 3) = -4 * ksi;
		dphi(0, 4) = 4 * eta;						dphi(1, 4) = 4 * ksi;
		dphi(0, 5) = -4 * eta;						dphi(1, 5) = 4 * (1 - ksi - 2 * eta);
		break;
	case 7:
		phi[0] = 1 - 3 * (ksi + eta) + 2 * (pow(ksi, 2) + pow(eta, 2)) + 7 * ksi*eta - 3 * ksi*eta*(ksi + eta);
		phi[1] = ksi * (-1 + 2 * ksi + 3 * eta - 3 * eta*(ksi + eta));
		phi[2] = eta * (-1 + 2 * ksi + 3 * eta - 3 * ksi*(ksi + eta));
		phi[3] = 4 * ksi*(1 - ksi - 4 * eta + 3 * eta*(ksi + eta));
		phi[4] = 4 * ksi*eta*(-2 + 3 * (ksi + eta));
		phi[5] = 4 * eta*(1 - 4 * ksi - eta + 3 * ksi*(ksi + eta));
		phi[6] = 27 * ksi*eta*(1 - ksi - eta);

		dphi(0, 0) = -3 + 4 * ksi + 7 * eta - 6 * ksi*eta - 3 * pow(eta, 2);
		dphi(0, 1) = -1 + 4 * ksi + 3 * eta - 6 * ksi*eta - 3 * pow(eta, 2);
		dphi(0, 2) = 3 * ksi*(1 - 2 * eta - ksi);
		dphi(0, 3) = 4 * (1 - 2 * ksi - 4 * eta + 6 * ksi*eta + 3 * pow(eta, 2));
		dphi(0, 4) = 4 * eta*(-2 + 6 * ksi + 3 * eta);
		dphi(0, 5) = 4 * eta*(-4 + 6 * ksi + 3 * eta);
		dphi(0, 6) = 27 * eta*(1 - 2 * ksi - eta);

		dphi(1, 0) = -3 + 7 * ksi + 4 * eta - 6 * ksi*eta - 3 * pow(ksi, 2);
		dphi(1, 1) = 3 * ksi*(1 - ksi - 2 * eta);
		dphi(1, 2) = -1 + 3 * ksi + 4 * eta - 6 * ksi*eta - 3 * pow(ksi, 2);
		dphi(1, 3) = 4 * ksi*(-4 + 3 * ksi + 6 * eta);
		dphi(1, 4) = 4 * ksi*(-2 + 3 * ksi + 6 * eta);
		dphi(1, 5) = 4 * (1 - 4 * ksi - 2 * eta + 6 * ksi*eta + 3 * pow(ksi, 2));
		dphi(1, 6) = 27 * ksi*(1 - ksi - 2 * eta);
		break;
	default:
		std::cout << "ShapeTriangle::Shape --> Invalid order" << std::endl;
		DebugStop();
		break;
	}
}

int ShapeTriangle::NShapeFunctions(int side, int order)
{
	if (order<0)
	{
		std::cout << "ShapeTriangle::NShapeFunctions --> Invalid shape function order on side " << side << std::endl;
		DebugStop();
	}

	switch (side)
	{
	case 0:
	case 1:
	case 2:
		return 1;
		break;
	case 3:
	case 4:
	case 5:
		return order - 1;
		break;
	case 6:
		return order - 2 < 0 ? 0 : ((order - 2)*(order - 1)) / 2;
		break;
	default:
		std::cout << "ShapeTriangle::NShapeFunctions --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

int ShapeTriangle::NShapeFunctions(VecInt &orders)
{
	if (orders.size() != nSides)
	{
		std::cout << "ShapeTriangle::NShapeFunctions --> Invalid dimention for 'orders' vector" << std::endl;
		DebugStop();
	}

	int nShapes = nCorners;

	for (int i = nCorners; i < nSides; i++)
	{
		nShapes += NShapeFunctions(i, orders[i - nCorners]);
	}

	return nShapes;
}