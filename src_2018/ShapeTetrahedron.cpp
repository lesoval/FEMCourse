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
	for (int i = 0; i < 3; i++)
	{
		if (xi[i]<0 || xi[i]>1)
		{
			std::cout << "ShapeTetrahedron::Shape --> Invalid argument 'xi[" << i << "]'" << std::endl;
			DebugStop();
		}
	}

	int nShapes = NShapeFunctions(orders);

	phi.resize(nShapes);
	dphi.Resize(3, nShapes);

	//Calcula os valores de phi e dphi para o ponto xi(ksi,eta,zeta)
	double ksi = xi[0];
	double eta = xi[1];
	double zeta = xi[2];

	switch (nShapes)
	{
	case 4:
		phi[0] = 1 - ksi - eta - zeta;
		phi[1] = ksi;
		phi[2] = eta;
		phi[3] = zeta;

		dphi(0, 0) = -1;	dphi(1, 0) = -1;	dphi(2, 0) = -1;
		dphi(0, 1) = 1;		dphi(1, 1) = 0;		dphi(2, 1) = 0;
		dphi(0, 2) = 0;		dphi(1, 2) = 1;		dphi(2, 2) = 0;
		dphi(0, 3) = 0;		dphi(1, 3) = 0;		dphi(2, 3) = 1;
		break;
	case 10:
		phi[0] = (1 - ksi - eta - zeta)*(1 - 2 * ksi - 2 * eta - 2 * zeta);
		phi[1] = ksi * (2 * ksi - 1);
		phi[2] = eta * (2 * eta - 1);
		phi[3] = zeta * (2 * zeta - 1);
		phi[4] = 4 * ksi*(1 - ksi - eta - zeta);
		phi[5] = 4 * ksi*eta;
		phi[6] = 4 * eta*(1 - ksi - eta - zeta);
		phi[7] = 4 * zeta*(1 - ksi - eta - zeta);
		phi[8] = 4 * ksi*zeta;
		phi[9] = 4 * eta*zeta;

		dphi(0, 0) = -1 + 2 * eta + 2 * ksi - 2 * (1 - eta - ksi - zeta) + 2 * zeta;
		dphi(0, 1) = -1 + 4 * ksi;
		dphi(0, 2) = 0;
		dphi(0, 3) = 0;
		dphi(0, 4) = -4 * ksi + 4 * (1 - eta - ksi - zeta);
		dphi(0, 5) = 4 * eta;
		dphi(0, 6) = -4 * eta;
		dphi(0, 7) = -4 * zeta;
		dphi(0, 8) = 4 * zeta;
		dphi(0, 9) = 0;

		dphi(1, 0) = -1 + 2 * eta + 2 * ksi - 2 * (1 - eta - ksi - zeta) + 2 * zeta;
		dphi(1, 1) = 0;
		dphi(1, 2) = -1 + 4 * eta;
		dphi(1, 3) = 0;
		dphi(1, 4) = -4 * ksi;
		dphi(1, 5) = 4 * ksi;
		dphi(1, 6) = -4 * eta + 4 * (1 - eta - ksi - zeta);
		dphi(1, 7) = -4 * zeta;
		dphi(1, 8) = 0;
		dphi(1, 9) = 4 * zeta;

		dphi(2, 0) = -1 + 2 * eta + 2 * ksi - 2 * (1 - eta - ksi - zeta) + 2 * zeta;
		dphi(2, 1) = 0;
		dphi(2, 2) = 0;
		dphi(2, 3) = -1 + 4*zeta;
		dphi(2, 4) = -4 * ksi;
		dphi(2, 5) = 0;
		dphi(2, 6) = -4 * eta;
		dphi(2, 7) = 4 * (1 - eta - ksi - zeta) - 4 * zeta;
		dphi(2, 8) = 4 * ksi;
		dphi(2, 9) = 4 * eta;
		break;
	default:
		std::cout << "ShapeTetrahedron::Shape --> Invalid order" << std::endl;
		DebugStop();
		break;
	}
}

int ShapeTetrahedron::NShapeFunctions(int side, VecInt &orders)
{
	if (orders.size() != 11)
	{
		std::cout << "ShapeTetrahedron::NShapeFunctions --> Invalid dimention for 'orders' vector" << std::endl;
	}

	for (int i = 0; i < 11; i++)
	{
		if (orders[i]<0)
		{
			std::cout << "ShapeTetrahedron::NShapeFunctions --> Invalid shape function order on side " << i + 4 << std::endl;
			DebugStop();
		}
	}

	int totsum, sum;
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
	case 8:
	case 9:
		return orders[side - 4] - 1;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
		sum = 0;
		if (orders[side - 4] != 0)
		{
			for (int i = 0; i < orders[side - 4] - 1; i++)
			{
				sum += i;
			}
		}
		return sum;
		break;
	case 14:
		totsum = 0;
		if (orders[side - 4] != 0)
		{
			for (int i = 1; i < orders[side - 4] - 2; i++)
			{
				sum = i * (i + 1) / 2;
				totsum += sum;
			}
		}
		return totsum;
		break;
	default:
		std::cout << "ShapeTetrahedron::NShapeFunctions --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

int ShapeTetrahedron::NShapeFunctions(VecInt &orders)
{
	int nCorners = 4;
	int nSides = 15;
	int nShapes = nCorners;

	for (int i = nCorners; i < nSides; i++)
	{
		nShapes += NShapeFunctions(i, orders);
	}

	return nShapes;
}