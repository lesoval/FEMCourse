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

GeomQuad::GeomQuad(const GeomQuad &copy)
{
	this->operator =(copy);
}

GeomQuad &GeomQuad::operator=(const GeomQuad &copy)
{
	fNodeIndices = copy.fNodeIndices;

	for (int i = 0; i<nSides; i++)
	{
		fNeighbours[i] = copy.fNeighbours[i];
	}

	return *this;
}

void GeomQuad::Shape(const VecDouble & xi, VecDouble & phi, Matrix & dphi)
{
	VecInt orders(nSides, 1);
	ShapeQuad::Shape(xi, orders, phi, dphi);
}

void GeomQuad::X(const VecDouble &xi, Matrix &NodeCo, VecDouble &x)
{
	int nRows = NodeCo.Rows();
	int nCols = NodeCo.Cols();

	VecDouble phi(4);
	Matrix dphi(2, 4);
	Shape(xi, phi, dphi);

	for (int i = 0; i < nRows; i++)
	{
		x[i] = 0;
		for (int j = 0; j < nCols; j++)
		{
			x[i] += phi[j] * NodeCo.GetVal(i, j);
		}
	}
}

void GeomQuad::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx)
{
	int nRows = NodeCo.Rows();
	int nCols = NodeCo.Cols();

	if (nCols != 4)
	{
		std::cout << "GeomQuad::GradX --> Objects of incompatible lengths, gradient cannot be computed." << std::endl;
		std::cout << "Nodes matrix must be spacex4." << std::endl;
		DebugStop();
	}

	gradx.Resize(nRows, 2);
	gradx.Zero();

	VecDouble phi(4);
	TMatrix dphi(2, 4);
	Shape(xi, phi, dphi);

	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0; j < nRows; j++)
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

void GeomQuad::SetNeighbour(int side, const GeoElementSide &neighbour)
{
	fNeighbours[side] = neighbour;
}