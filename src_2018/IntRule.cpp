/*
 *  IntRule.cpp
 *
 *  Created by Leandro Valdez on 4/5/18.
 *
 */

#include <iomanip>
#include "IntRule.h"
#include "tpanic.h"

IntRule::IntRule(){}

IntRule::IntRule(int order)
{
	if (order<0)
	{
		DebugStop();
	}
	SetOrder(order);
}

IntRule::~IntRule(void){}

void IntRule::operator=(const IntRule &copy)
{
	fOrder = copy.fOrder;
	fPoints = copy.fPoints;
	fWeights = copy.fWeights;
}

IntRule::IntRule(const IntRule &copy) :
	fOrder(copy.fOrder), fPoints(copy.fPoints), fWeights(copy.fWeights)
{

}

int IntRule::NPoints() const
{
	return fPoints.Rows();
}

void IntRule::Point(int p, VecDouble &co, double &weight) const
{
	if (p<0 || p >= NPoints())
	{
		DebugStop();
	}

	for (int i = 0; i < fPoints.Cols(); i++)
	{
		co[i] = fPoints.GetVal(p, i);
	}

	weight = fWeights[p];
	
}

void IntRule::Print(std::ostream &out) const
{
	out << "ORDER	" << fOrder << "	NPoints	" << NPoints() << "\n" << std::endl;

	for (int i = 0; i < NPoints(); i++)
	{
		VecDouble co(NPoints());
		double weight;
		Point(i, co, weight);
		std::cout << std::setprecision(12) << std::fixed;
		out << "POINT	" << i << "	POS {";
		for (int j = 0; j < fPoints.Cols(); j++)
		{
			if (j!=0)
			{
				out << ", ";
			}
			out << co[j];
		}
		out << "}	WEIGHT " << weight << std::endl;
	}
}