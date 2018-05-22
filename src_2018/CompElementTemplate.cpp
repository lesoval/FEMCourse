/*
*  CompElementTemplate.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "CompElementTemplate.h"
#include "CompMesh.h"

template<class Shape>
CompElementTemplate<Shape>::CompElementTemplate() {}

template<class Shape>
CompElementTemplate<Shape>::CompElementTemplate(int64_t ind, CompMesh *cmesh, GeoElement * geo) : CompElement(ind, cmesh, geo)
{
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
	VecInt orders(NDOF());
	Shape::Shape(intpoint, orders, phi, dphi);
	CompMesh *cmesh = this->GetCompMesh();
}

template<class Shape>
int CompElementTemplate<Shape>::NShapeFunctions() const
{
	return 0;
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
int CompElementTemplate<Shape>::NDOF() const
{
	return dofindexes.size();
}

template<class Shape>
int CompElementTemplate<Shape>::NShapeFunctions(int doflocindex) const
{
	CompMesh cmesh = GetCompMesh();
	DOF dof = cmesh.GetDOF(doflocindex);
	
	return dof.GetNShape();
}

template<class Shape>
int CompElementTemplate<Shape>::ComputeNShapeFunctions(int doflocindex, int order)
{
	dofindexes.resize(doflocindex + 1);
	dofindexes[doflocindex] = doflocindex;

	return Shape::NShapeFunctions(doflocindex, order);
}

template class CompElementTemplate<Shape1d>;
template class CompElementTemplate<ShapeQuad>;
template class CompElementTemplate<ShapeTriangle>;
template class CompElementTemplate<ShapeTetrahedron>;