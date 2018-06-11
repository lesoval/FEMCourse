/*
*  GeomElement.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoElement.h"
#include "CompElementTemplate.h"
#include "Shape1d.h"
#include "ShapeQuad.h"
#include "ShapeTriangle.h"
#include "ShapeTetrahedron.h"
#include "tpanic.h"

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

CompElement * GeoElement::CreateCompEl(CompMesh * mesh, int64_t index)
{
	switch (this->Type())
	{
	case EOned:

		return new CompElementTemplate<Shape1d>(index, mesh, this);
		break;

	case EQuadrilateral:

		return new CompElementTemplate<ShapeQuad>(index, mesh, this);
		break;

	case ETriangle:

		return new CompElementTemplate<ShapeTriangle>(index, mesh, this);
		break;

	case ETetraedro:

		return new CompElementTemplate<ShapeTetrahedron>(index, mesh, this);
		break;

	default:
		std::cout << "GeoElement::CreateCompEl -> Not implemented element type" << std::endl;
		DebugStop();
		break;
	}
	return 0;
}

void GeoElement::Print(std::ostream & out) {}
