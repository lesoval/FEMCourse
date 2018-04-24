/*
*  IntRuleQuad.cpp
*
*  Created by Leandro Valdez on 4/5/18.
*
*/

#include "IntRuleQuad.h"
#include "tpanic.h"

IntRuleQuad::IntRuleQuad() :IntRule() {}

IntRuleQuad::IntRuleQuad(int order)
{
	SetOrder(order);

	// Calcula o número de pontos necessários para integração
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
	npoints = pow(npoints, 2);

	//Calcula os pontos e pesos básicos de Gauss
	int n = sqrt(npoints);
	VecDouble points(n);
	VecDouble weights(n);

	fPoints.Resize(npoints, 2);
	fWeights.resize(npoints);

	gaulegQuad(-1, 1, points, weights);

	for (int i = 0; i<n; i++) {

		for (int j = 0; j<n; j++) {
			fWeights[j + i * n] = weights[j] * weights[i];
			fPoints.PutVal(j + i * n, 0, points[j]);
			fPoints.PutVal(j + i * n, 1, points[i]);
		}
	}
}

void IntRuleQuad::SetOrder(int order)
{
	if (order<0)
	{
		DebugStop();
	}

	fOrder = order;
}

void IntRuleQuad::gaulegQuad(const double x1, const double x2, VecDouble &x, VecDouble &w)
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