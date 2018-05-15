/*
*  CompElement.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "CompElement.h"

CompElement::CompElement() {}

CompElement::CompElement(int64_t index, GeoElement *geo)
{
	this->index = index;
	geoel = geo;
}

CompElement::CompElement(const CompElement &copy)
{
	this->operator=(copy);
}

CompElement &CompElement::operator=(const CompElement &copy)
{
	index = copy.index;
	geoel = copy.geoel;
	compmesh = copy.compmesh;
	intrule = copy.intrule;
	mat = copy.mat;

	return *this;
}

CompElement::~CompElement() {}

CompElement *CompElement::Clone() const
{
	return 0;
}

MathStatement *CompElement::GetStatement() const
{
	return mat;
}

void CompElement::SetStatement(MathStatement *statelement)
{
	mat = statelement;
}

IntRule *CompElement::GetIntRule() const
{
	return intrule;
}

void CompElement::SetIntRule(IntRule *intrule)
{
	this->intrule = intrule;
}

void CompElement::SetIndex(int64_t ind)
{
	index = ind;
}

GeoElement *CompElement::GetGeoElement() const
{
	return geoel;
}

void CompElement::SetGeoElement(GeoElement *element)
{
	geoel = element;
}

CompMesh *CompElement::GetCompMesh() const
{
	return compmesh;
}

void CompElement::SetCompMesh(CompMesh *mesh)
{
	compmesh = mesh;
}

void CompElement::InitializeIntPointData(IntPointData &data) const
{

}

void CompElement::ComputeRequiredData(IntPointData &data, VecDouble &intpoint) const
{

}

void CompElement::CalcStiff(Matrix &ek, Matrix &ef) const
{

}