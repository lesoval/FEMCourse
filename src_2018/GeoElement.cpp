/*
*  GeomElement.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoElement.h"

GeoElement::GeoElement() {}

GeoElement::GeoElement(int materialid, GeoMesh * mesh, int index)
{
	this->MaterialId = materialid;
	this->GMesh = mesh;
	this->Index = index;
}

GeoElement::~GeoElement() {}

GeoElement::GeoElement(const GeoElement &copy)
{
	GMesh = copy.GMesh;
	MaterialId = copy.MaterialId;
}

void GeoElement::Print(std::ostream & out) {}
