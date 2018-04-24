/*
*  GeomTetrahedron.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeomTetrahedron.h"
#include "tpanic.h"

GeomTetrahedron::GeomTetrahedron() {}

GeomTetrahedron::~GeomTetrahedron() {}

GeomTetrahedron::GeomTetrahedron(const GeomTetrahedron &copy) :fNodeIndices(copy.fNodeIndices) {}

GeomTetrahedron &GeomTetrahedron::operator=(const GeomTetrahedron &copy)
{
	return *this;
}

void GeomTetrahedron::Shape(const VecDouble &xi, VecDouble &phi, TMatrix &dphi)
{
	phi[0] = 1.0 - xi[0] - xi[1] - xi[2];
	phi[1] = xi[0];
	phi[2] = xi[1];
	phi[3] = xi[2];

	dphi(0, 0) = -1.0;	dphi(1, 0) = -1.0;	dphi(2, 0) = -1.0;
	dphi(0, 1) = 1.0;	dphi(1, 1) = 0.0;	dphi(2, 1) = 0.0;
	dphi(0, 2) = 0.0;	dphi(1, 2) = 1.0;	dphi(2, 2) = 0.0;
	dphi(0, 3) = 0.0;	dphi(1, 3) = 0.0;	dphi(2, 3) = 1.0;
}

void GeomTetrahedron::X(const VecDouble &xi, TMatrix &NodeCo, VecDouble &x)
{
	
}

void GeomTetrahedron::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx)
{
	gradx.Resize(NodeCo.Rows(), 3);
	gradx.Zero();

	VecDouble phi(4);
	TMatrix dphi(3, 4);
	Shape(xi, phi, dphi);

	for (int i = 0; i < NodeCo.Cols(); i++)
	{
		for (int j = 0; j < NodeCo.Rows(); j++)
		{
			gradx(j, 0) += NodeCo(j, i)*dphi(0, i);
			gradx(j, 1) += NodeCo(j, i)*dphi(1, i);
			gradx(j, 2) += NodeCo(j, i)*dphi(2, i);
		}
	}
}

int GeomTetrahedron::NumNodes()
{
	return nCorners;
}

void GeomTetrahedron::SetNodes(const VecInt &nodes)
{
	fNodeIndices = nodes;
}

void GeomTetrahedron::GetNodes(VecInt &nodes)
{
	nodes = fNodeIndices;
}

int GeomTetrahedron::NodeIndex(int node)
{
	return fNodeIndices[node];
}

GeoElementSide GeomTetrahedron::Neighbour(int side)
{
	return fNeighbours[side];
}

void GeomTetrahedron::SetNeighbour(int side, GeoElementSide &neighbour)
{
	fNeighbours[side] = neighbour;
}