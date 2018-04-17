/*
*  IntRule.cpp
*
*  Created by Leandro Valdez on 5/4/18.
*
*/

#include <iomanip>
#include "IntRule1d.h"
#include "tpanic.h"

IntRule1d::IntRule1d():IntRule(){}

IntRule1d::IntRule1d(int order) :IntRule(order){}

int IntRule1d::NPoints() const
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
	return npoints;
}

void IntRule1d::Point(int p, VecDouble &co, double &weight)
{
	fPoints.Resize(NPoints(), 1);
	fWeights.resize(NPoints());

	if (p<0 || p >= NPoints())
	{
		DebugStop();
	}

	gauleg(-1, 1, fPoints, fWeights);

	co.resize(1);

	co[0] = fPoints.GetVal(p,0);
	weight = fWeights[p];
}

void IntRule1d::Print(std::ostream &out) const
{
	out << "ORDER	" << fOrder << "	NPoints	" << NPoints() << "\n" << std::endl;

	for (int i = 0; i < NPoints(); i++)
	{
		VecDouble co(NPoints());
		double weight;
		IntRule1d T(fOrder);
		T.Point(i, co, weight);
		std::cout << std::setprecision(12) << std::fixed;
		out << "POINT	" << i << "	POS " << co[0] << "	WEIGHT " << weight << std::endl;
	}
}

void IntRule1d::gauleg(const double x1, const double x2, TMatrix &x, VecDouble &w)
{
	const double EPS = 1.0e-14;
	double z1, z, xm, xl, pp, p3, p2, p1;
	int n = x.Rows();
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
		x.PutVal(i,0, xm - xl * z);
		x.PutVal(n - 1 - i,0, xm + xl * z);
		w[i] = 2.0*xl / ((1.0 - z * z)*pp*pp);
		w[n - 1 - i] = w[i];
	}
}