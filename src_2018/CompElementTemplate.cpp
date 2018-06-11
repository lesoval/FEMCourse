/*
*  CompElementTemplate.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "CompElementTemplate.h"
#include "CompElement.h"
#include "GeoElement.h"
#include "CompMesh.h"
#include "Shape1d.h"
#include "ShapeQuad.h"
#include "ShapeTetrahedron.h"
#include "ShapeTriangle.h"

template<class Shape>
CompElementTemplate<Shape>::CompElementTemplate() : CompElement() {}

template<class Shape>
CompElementTemplate<Shape>::CompElementTemplate(int64_t ind, CompMesh *cmesh, GeoElement * geo) : CompElement(ind, cmesh, geo)
{
	int order = cmesh->GetDefaultOrder();
	int nShapes = this->NShapeFunctions();

	SetIntRule(&intrule);
	intrule.SetOrder(order);

	SetNDOF(nShapes);
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
void CompElementTemplate<Shape>::ShapeFunctions(const VecDouble & intpoint, VecDouble & phi, Matrix & dphi) const
{
	int order = GetCompMesh()->GetDefaultOrder();
	int nSides = GetGeoElement()->NSides();
	VecInt orders(nSides, order);

	Shape::Shape(intpoint, orders, phi, dphi);
}

template<class Shape>
void CompElementTemplate<Shape>::GetMultiplyingCoeficients(VecDouble & coefs) const
{
}

template<class Shape>
int CompElementTemplate<Shape>::NShapeFunctions() const
{
	int order = GetCompMesh()->GetDefaultOrder();
	int nSides = GetGeoElement()->NSides();
	VecInt orders(nSides, order);

	int nShapes = Shape::NShapeFunctions(orders);

	return nShapes;
}

template<class Shape>
void CompElementTemplate<Shape>::SetNDOF(int64_t ndof)
{
	dofindexes.resize(ndof);
}

template<class Shape>
void CompElementTemplate<Shape>::SetDOFIndex(int i, int64_t dofindex)
{
	dofindexes[i] = dofindex;
}

template<class Shape>
int64_t CompElementTemplate<Shape>::GetDOFIndex(int i)
{
	return dofindexes[i];
}

template<class Shape>
int CompElementTemplate<Shape>::NDOF() const
{
	return dofindexes.size();
}

template<class Shape>
int CompElementTemplate<Shape>::NShapeFunctions(int doflocindex) const
{
	return GetCompMesh()->GetDOF(doflocindex).GetNShape();
}

template<class Shape>
int CompElementTemplate<Shape>::ComputeNShapeFunctions(int doflocindex, int order)
{
	return Shape::NShapeFunctions(doflocindex, order);
}

template class CompElementTemplate<Shape1d>;
template class CompElementTemplate<ShapeQuad>;
template class CompElementTemplate<ShapeTriangle>;
template class CompElementTemplate<ShapeTetrahedron>;