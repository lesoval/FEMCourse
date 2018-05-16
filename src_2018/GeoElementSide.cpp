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
}

void GeoElementSide::SetNeighbour(const GeoElementSide & neighbour)
{
}

bool GeoElementSide::IsNeighbour(const GeoElementSide & candidate)
{
	return false;
}

void GeoElementSide::IsertConnectivity(GeoElementSide & connectivity)
{
}

void GeoElementSide::AllNeighbours(std::vector<GeoElementSide>& allneigh)
{
	GeoElementSide NodeNeigh = Neighbour();

	while (*this != NodeNeigh)//Enquanto o elemento não repete, prossiga
	{
		allneigh.push_back(NodeNeigh);//Insere o vizinho do nó "k" na vizinhança do lado "j"
		NodeNeigh = NodeNeigh.Neighbour();//Copia o próximo vizinho do nó "k"
	}
}

void GeoElementSide::ComputeNeighbours(std::vector<GeoElementSide> neighbour)
{
}

void GeoElementSide::Intersect(const std::vector<int>& one, const std::vector<int>& two, std::vector<int>& result)
{
}

void GeoElementSide::Intersect(const std::vector<int>& one, const std::vector<int>& two, const std::vector<int>& three, std::vector<int>& result)
{
}