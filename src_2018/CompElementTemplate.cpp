/*
*  CompElementTemplate.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "CompElementTemplate.h"

template<class Shape>
CompElementTemplate<Shape>::CompElementTemplate() {}

template<class Shape>
CompElementTemplate<Shape>::CompElementTemplate(int64_t index, GeoElement * geo) : CompElement(index, geo)
{
	this->GetCompMesh()->SetElement(index, this);
}

template<class Shape>
CompElementTemplate<Shape>::CompElementTemplate(const CompElementTemplate &copy) : CompElement(copy)
{
	this->operator=(copy);
}

template<class Shape>
CompElementTemplate<Shape> & CompElementTemplate<Shape>::operator=(const CompElementTemplate &copy)
{
	dofindexes = copy.dofindexes;
	intrule = copy.intrule;

	return *this;
}

template<class Shape>
CompElementTemplate<Shape>::~CompElementTemplate() {}

template<class Shape>
CompElement * CompElementTemplate<Shape>::Clone() const
{
	CompElement *compelement = new CompElementTemplate(*this);
	return compelement;
}

template<class Shape>
void CompElementTemplate<Shape>::ShapeFunctions(const VecDouble & intpoint, VecDouble & phi, Matrix & dphi)
{
}

template<class Shape>
int CompElementTemplate<Shape>::NShapeFunctions()
{
	return 0;
}

template<class Shape>
int CompElementTemplate<Shape>::NDOF()
{
	return 0;
}

template<class Shape>
int CompElementTemplate<Shape>::NShapeFunctions(int doflocindex)
{
	return 0;
}

template<class Shape>
int CompElementTemplate<Shape>::ComputeNShapeFunctions(int doflocindex, int order)
{
	return 0;
}

