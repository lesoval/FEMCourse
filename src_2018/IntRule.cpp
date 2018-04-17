/*
 *  IntRule.cpp
 *
 *  Created by Leandro Valdez on 5/4/18.
 *
 */

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

void IntRule::SetOrder(int order)
{
	fOrder = order;
}

void IntRule::operator=(const IntRule &copy)
{
	fOrder = copy.fOrder;
	fPoints = copy.fPoints;
	fWeights = copy.fWeights;
}

IntRule::IntRule(const IntRule &copy)
{
	fOrder = copy.fOrder;
	fPoints = copy.fPoints;
	fWeights = copy.fWeights;
}

int IntRule::NPoints() const
{
	return 0;
}

void IntRule::Point(int p, VecDouble &co, double &weight){}

void IntRule::Print(std::ostream &out) const
{
	out << "ORDER	" << fOrder << "	NPoints	" << NPoints() << "\n" << std::endl;
}