/*
*  IntRule.cpp
*
*  Created by Leandro Valdez on 5/4/18.
*
*/

#include <iomanip>
#include <math.h>
#include "IntRuleQuad.h"
#include "tpanic.h"

IntRuleQuad::IntRuleQuad() :IntRule() {}

IntRuleQuad::IntRuleQuad(int order) : IntRule(order) {}

int IntRuleQuad::NPoints() const
{
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
	return pow(npoints,2);
}

void IntRuleQuad::Point(int p, VecDouble &co, double &weight)
{
	fPoints.Resize(NPoints(), 2);
	fWeights.resize(NPoints());

	if (p<0 || p >= NPoints())
	{
		DebugStop();
	}

	gaulegQuad(-1, 1, fPoints, fWeights);

	co.resize(2);

	co[0] = fPoints.GetVal(p, 0);
	co[1] = fPoints.GetVal(p, 1);
	weight = fWeights[p];
}

void IntRuleQuad::Print(std::ostream &out) const
{
	out << "ORDER	" << fOrder << "	NPoints	" << NPoints() << "\n" << std::endl;

	for (int i = 0; i < NPoints(); i++)
	{
		VecDouble co(NPoints());
		double weight;
		IntRuleQuad T(fOrder);
		T.Point(i, co, weight);
		std::cout << std::setprecision(12) << std::fixed;
		out << "POINT	" << i << "	POS {" << co[0] << ", " << co[1]
			<< "}	WEIGHT " << weight << std::endl;
	}
}

void IntRuleQuad::gaulegQuad(const double x1, const double x2, TMatrix &x, VecDouble &w)
{
	const double EPS = 1.0e-14;
	double z1, z, xm, xl, pp, p3, p2, p1;
	int n = sqrt(x.Rows());
	int m = (n + 1) / 2;
	xm = 0.5*(x2 + x1);
	xl = 0.5*(x2 - x1);
	VecDouble co(n);
	VecDouble weight(n);
	for (int i = 0; i<m; i++) {
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
		co[i] = xm - xl * z;
		co[n - 1 - i] = xm + xl * z;
		weight[i] = 2.0*xl / ((1.0 - z * z)*pp*pp);
		weight[n - 1 - i] = weight[i];
	}

	for (int i = 0; i<n; i++) {

		for (int j = 0; j<n; j++) {
			w[j + i * n] = weight[j] * weight[i];
			x.PutVal(j + i * n,0,co[j]);
			x.PutVal(j + i * n, 1, co[i]);
		}
	}
}