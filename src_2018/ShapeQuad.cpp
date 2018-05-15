/*
*  ShapeQuad.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "ShapeQuad.h"
#include "tpanic.h"

void ShapeQuad::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi)
{
	for (int i = 0; i < Dimension; i++)
	{
		if (xi[i]<-1 || xi[i]>1)
		{
			std::cout << "ShapeQuad::Shape --> Invalid coordinade 'xi[" << i << "]'" << std::endl;
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
	case 4:
		phi[0] = (1 - ksi)*(1 - eta) / 4;
		phi[1] = (1 + ksi)*(1 - eta) / 4;
		phi[2] = (1 + ksi)*(1 + eta) / 4;
		phi[3] = (1 - ksi)*(1 + eta) / 4;

		dphi(0, 0) = -(1 - eta) / 4;		dphi(1, 0) = -(1 - ksi) / 4;
		dphi(0, 1) = (1 - eta) / 4;			dphi(1, 1) = -(1 + ksi) / 4;
		dphi(0, 2) = (1 + eta) / 4;			dphi(1, 2) = (1 + ksi) / 4;
		dphi(0, 3) = -(1 + eta) / 4;		dphi(1, 3) = (1 - ksi) / 4;
		break;
	case 8:
		phi[0] = (1 - ksi)*(1 - eta)*(-1 - ksi - eta) / 4;
		phi[1] = (1 + ksi)*(1 - eta)*(-1 + ksi - eta) / 4;
		phi[2] = (1 + ksi)*(1 + eta)*(-1 + ksi + eta) / 4;
		phi[3] = (1 - ksi)*(1 + eta)*(-1 - ksi + eta) / 4;
		phi[4] = (1 - pow(ksi, 2))*(1 - eta) / 2;
		phi[5] = (ksi + 1)*(1 - pow(eta, 2)) / 2;
		phi[6] = (1 - pow(ksi, 2))*(1 + eta) / 2;
		phi[7] = (ksi - 1)*(1 - pow(eta, 2)) / 2;

		dphi(0, 0) = (1 - eta)*(2 * ksi + eta) / 4;			dphi(1, 0) = (1 - ksi)*(ksi + 2 * eta) / 4;
		dphi(0, 1) = (1 - eta)*(2 * ksi - eta) / 4;			dphi(1, 1) = -(1 + ksi)*(ksi - 2 * eta) / 4;
		dphi(0, 2) = (1 + eta)*(2 * ksi + eta) / 4;			dphi(1, 2) = (1 + ksi)*(ksi + 2 * eta) / 4;
		dphi(0, 3) = -(1 + eta)*(-2 * ksi + eta) / 4;		dphi(1, 3) = (1 - ksi)*(-ksi + 2 * eta) / 4;
		dphi(0, 4) = -ksi * (1 - eta);						dphi(1, 4) = -(1 - pow(ksi, 2)) / 2;
		dphi(0, 5) = (1 - pow(eta, 2)) / 2;					dphi(1, 5) = -eta * (1 + ksi);
		dphi(0, 6) = -ksi * (1 + eta);						dphi(1, 6) = (1 - pow(ksi, 2)) / 2;
		dphi(0, 7) = -(1 - pow(eta, 2)) / 2;				dphi(1, 7) = -eta * (1 - ksi);
		break;
	case 9:
		phi[0] = ksi * eta*(ksi - 1)*(eta - 1) / 4;
		phi[1] = ksi * eta*(ksi + 1)*(eta - 1) / 4;
		phi[2] = ksi * eta*(ksi + 1)*(eta + 1) / 4;
		phi[3] = ksi * eta*(ksi - 1)*(eta + 1) / 4;
		phi[4] = (1 - pow(ksi, 2))*eta*(eta - 1) / 2;
		phi[5] = ksi * (ksi + 1)*(1 - pow(eta, 2)) / 2;
		phi[6] = (1 - pow(ksi, 2))*eta*(eta + 1) / 2;
		phi[7] = ksi * (ksi - 1)*(1 - pow(eta, 2)) / 2;
		phi[8] = (1 - pow(ksi, 2))*(1 - pow(eta, 2)) / 2;

		dphi(0, 0) = (2 * ksi - 1)*eta*(eta - 1) / 4;			dphi(1, 0) = ksi * (ksi - 1)*(2 * eta - 1) / 4;
		dphi(0, 1) = (2 * ksi + 1)*eta*(eta - 1) / 4;			dphi(1, 1) = ksi * (ksi + 1)*(2 * eta - 1) / 4;
		dphi(0, 2) = (2 * ksi + 1)*eta*(eta + 1) / 4;			dphi(1, 2) = ksi * (ksi + 1)*(2 * eta + 1) / 4;
		dphi(0, 3) = (2 * ksi - 1)*eta*(eta + 1) / 4;			dphi(1, 3) = ksi * (ksi - 1)*(2 * eta + 1) / 4;
		dphi(0, 4) = -ksi * eta*(eta - 1);						dphi(1, 4) = (1 - pow(ksi, 2))*(2 * eta - 1) / 2;
		dphi(0, 5) = (2 * ksi + 1)*(1 - pow(eta, 2)) / 2;		dphi(1, 5) = -ksi * eta*(ksi + 1);
		dphi(0, 6) = -ksi * eta*(eta + 1);						dphi(1, 6) = (1 - pow(ksi, 2))*(2 * eta + 1) / 2;
		dphi(0, 7) = (2 * ksi - 1)*(1 - pow(eta, 2)) / 2;		dphi(1, 7) = -ksi * eta*(ksi + 1);
		dphi(0, 8) = -2 * ksi*(1 - pow(eta, 2));				dphi(1, 8) = -2 * eta*(1 - pow(ksi, 2));
		break;
	default:
		std::cout << "ShapeQuad::Shape --> Invalid order" << std::endl;
		DebugStop();
		break;
	}
}

int ShapeQuad::NShapeFunctions(int side, int order)
{
	if (order<0)
	{
		std::cout << "ShapeQuad::NShapeFunctions --> Invalid shape function order on side " << side << std::endl;
		DebugStop();
	}

	switch (side)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return 1;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		return order - 1;
		break;
	case 8:
		return pow(order - 1, 2);
	default:
		std::cout << "ShapeQuad::NShapeFunctions --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

int ShapeQuad::NShapeFunctions(VecInt &orders)
{
	if (orders.size() != nSides)
	{
		std::cout << "ShapeQuad::NShapeFunctions --> Invalid dimention for 'orders' vector" << std::endl;
		DebugStop();
	}

	int nShapes = nCorners;

	for (int i = nCorners; i < nSides; i++)
	{
		nShapes += NShapeFunctions(i, orders[i - nCorners]);
	}

	return nShapes;
}