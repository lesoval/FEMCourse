/*
*  GeomQuad.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeomQuad.h"
#include "tpanic.h"

GeomQuad::GeomQuad() {}

GeomQuad::~GeomQuad() {}

GeomQuad::GeomQuad(const GeomQuad &copy) :fNodeIndices(copy.fNodeIndices) {}

GeomQuad &GeomQuad::operator=(const GeomQuad &copy)
{
	return *this;
}

void GeomQuad::Shape(const VecDouble &xi, VecDouble &phi, TMatrix &dphi)
{
	phi[0] = (1 - xi[0])*(1 - xi[1]) / 4;
	phi[1] = (1 + xi[0])*(1 - xi[1]) / 4;
	phi[2] = (1 + xi[0])*(1 + xi[1]) / 4;
	phi[3] = (1 - xi[0])*(1 + xi[1]) / 4;

	dphi(0, 0) = (xi[1] - 1) / 4;	dphi(1, 0) = (xi[0] - 1) / 4;
	dphi(0, 1) = (1 - xi[1]) / 4;	dphi(1, 1) = (1 - xi[0]) / 4;
	dphi(0, 2) = (xi[1] + 1) / 4;	dphi(1, 2) = (xi[0] + 1) / 4;
	dphi(0, 3) = (1 - xi[1]) / 4;	dphi(1, 3) = (1 - xi[0]) / 4;
}

void GeomQuad::X(const VecDouble &xi, TMatrix &NodeCo, VecDouble &x)
{
	
}

void GeomQuad::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx)
{
	gradx.Resize(NodeCo.Rows(), 2);
	gradx.Zero();

	VecDouble phi(4);
	TMatrix dphi(2, 4);
	Shape(xi, phi, dphi);

	for (int i = 0; i < NodeCo.Cols(); i++)
	{
		for (int j = 0; j < NodeCo.Rows(); j++)
		{
			gradx(j, 0) += NodeCo.GetVal(j, i)*dphi(0, i);
			gradx(j, 1) += NodeCo.GetVal(j, i)*dphi(1, i);
		}
	}
}

int GeomQuad::NumNodes()
{
	return nCorners;
}

void GeomQuad::SetNodes(const VecInt &nodes)
{
	fNodeIndices = nodes;
}

void GeomQuad::GetNodes(VecInt &nodes)
{
	nodes = fNodeIndices;
}

int GeomQuad::NodeIndex(int node)
{
	return fNodeIndices[node];
}

GeoElementSide GeomQuad::Neighbour(int side)
{
	return fNeighbours[side];
}

void GeomQuad::SetNeighbour(int side, GeoElementSide &neighbour)
{
	fNeighbours[side] = neighbour;
}