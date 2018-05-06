/*
*  GeomMesh.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoMesh.h"

GeoMesh::GeoMesh(const GeoMesh &copy)
{
	this->operator=(copy);
}

GeoMesh &GeoMesh::operator=(const GeoMesh &copy)
{
	Nodes = copy.Nodes;
	Elements = copy.Elements;

	return *this;
}

void GeoMesh::SetNumNodes(int nnodes)
{
	Nodes.resize(nnodes);
}

void GeoMesh::SetNumElements(int numelements)
{
	Elements.resize(numelements);
}

int GeoMesh::NumNodes()
{
	return Nodes.size();
}

int GeoMesh::NumElements()
{
	return Elements.size();
}

GeoNode &GeoMesh::Node(int node)
{
	return Nodes[node];
}

void GeoMesh::SetElement(int elindex, GeoElement *gel)
{
	Elements[elindex] = gel;
}

GeoElement *GeoMesh::Element(int elindex)
{
	return Elements[elindex];
}

void GeoMesh::BuildConnectivity()
{
	
}

void GeoMesh::Print(std::ostream &out)
{

}