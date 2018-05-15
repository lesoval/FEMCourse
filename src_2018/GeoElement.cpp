/*
*  GeomElement.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoElement.h"

GeoElement::GeoElement() {}

GeoElement::~GeoElement() {}

GeoElement::GeoElement(const GeoElement &copy)
{
	GMesh = copy.GMesh;
	MaterialId = copy.MaterialId;
}


void GeoElement::Print(std::ostream &out)
{
	out << "ELEMENT: " << Index << "\tTYPE: " << Type() << "\t\tMatID: " << MaterialId << "\tNODES(";
	for (int i = 0; i < NNodes(); i++)
	{
		if (i != 0)
		{
			out << ", ";
		}
		out << NodeIndex(i);
	}
	out << ") " << std::endl;
}