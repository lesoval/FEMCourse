/*
*  IntRule1d.cpp
*
*  Created by Leandro Valdez on 4/5/18.
*
*/

#include "IntRule1d.h"
#include "tpanic.h"

IntRule1d::IntRule1d():IntRule(){}

IntRule1d::IntRule1d(int order)
{
	SetOrder(order);
}

void IntRule1d::SetOrder(int order)
{
	if (order<0)
	{
		std::cout << "IntRule1d::SetOrder --> Invalid argument 'order'" << std::endl;
		DebugStop();
	}

	fOrder = order;

	// Define o número de pontos necessários para integração
	int npoints, resto;
	resto = fOrder % 2;

	if (resto != 0)
	{
		npoints = (fOrder + 1) / 2;	//para fOrder impar
	}
	if (resto == 0)
	{
		npoints = (fOrder + 2) / 2;	//para fOrder par
	}

	//Calcula os pontos e pesos básicos de Gauss
	VecDouble points(npoints);

	fPoints.Resize(npoints, 1);
	fWeights.resize(npoints);

	gauleg(-1, 1, points, fWeights);

	for (int i = 0; i < npoints; i++)
	{
		fPoints.PutVal(i, 0, points[i]);
	}
}

void IntRule1d::gauleg(const double x1, const double x2, VecDouble &x, VecDouble &w)
{
	const double EPS = 1.0e-14;
	double z1, z, xm, xl, pp, p3, p2, p1;
	int n = x.size();
	int m = (n + 1) / 2;
	xm = 0.5*(x2 + x1);
	xl = 0.5*(x2 - x1);
	for (int i = 0; i<m; i++)
	{
		z = cos(3.141592654*(i + 0.75) / (n + 0.5));
		do {
			p1 = 1.0;
			p2 = 0.0;
			for (int j = 0; j<n; j++) {
				p3 = p2;
				p2 = p1;
				p1 = ((2.0*j + 1.0)*z*p2 - j * p3) / (j + 1);
			}
			pp = n * (z*p1 - p2) / (z*z - 1.0);
			z1 = z;
			z = z1 - p1 / pp;
		} while (abs(z - z1) > EPS);
		x[i] = xm - xl * z;
		x[n - 1 - i] = xm + xl * z;
		w[i] = 2.0*xl / ((1.0 - z * z)*pp*pp);
		w[n - 1 - i] = w[i];
	}
}