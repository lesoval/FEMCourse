/*
*  GeomElementSide.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoElementSide.h"

GeoElementSide::GeoElementSide() {}

GeoElementSide::GeoElementSide(const GeoElementSide &copy)
{
	this->operator=(copy);
}

GeoElementSide &GeoElementSide::operator=(const GeoElementSide &copy)
{
	fSide = copy.fSide;
	fElement = copy.fElement;

	return *this;
}

GeoElementSide GeoElementSide::Neighbour() const
{
	return fElement->Neighbour(fSide);
};