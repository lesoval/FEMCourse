/*
*  Geom1d.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "Geom1d.h"
#include "tpanic.h"

Geom1d::Geom1d(){}

Geom1d::~Geom1d(){}

Geom1d::Geom1d(const Geom1d &copy)
{
	this->operator=(copy);
}

Geom1d &Geom1d::operator=(const Geom1d &copy)
{
	fNodeIndices = copy.fNodeIndices;

	for (int i = 0; i<nSides; i++)
	{
		fNeighbours[i] = copy.fNeighbours[i];
	}

	return *this;
}

void Geom1d::Shape(const VecDouble &xi, VecDouble &phi, Matrix &dphi)
{
	VecInt orders(nSides, 1);
	Shape1d::Shape(xi, orders, phi, dphi);
}

void Geom1d::X(const VecDouble &xi, Matrix &NodeCo, VecDouble &x)
{
	int nRows = NodeCo.Rows();

	for (int i = 0; i < nRows; i++)
	{
		x[i] = NodeCo.GetVal(i, 0)*(1 - xi[i]) / 2 + NodeCo.GetVal(i, 1)*(1 + xi[i]) / 2;
	}
}

void Geom1d::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx)
{
	int nRows = NodeCo.Rows();
	int nCols = NodeCo.Cols();

	if (nCols != 2)
	{
		std::cout << "Geom1d::GradX --> Objects of incompatible lengths, gradient cannot be computed." << std::endl;
		std::cout << "Nodes matrix must be spacex2." << std::endl;
		DebugStop();
	}

	gradx.Resize(nRows, 1);
	gradx.Zero();

	VecDouble phi(2);
	TMatrix dphi(2, 2);
	Shape(xi, phi, dphi);

	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0; j < nRows; j++)
		{
			gradx(j, 0) += NodeCo.GetVal(j, i)*dphi(0, i);
		}
	}
}

int Geom1d::NumNodes()
{
	return nCorners;
}

void Geom1d::SetNodes(const VecInt &nodes)
{
	fNodeIndices = nodes;
}

void Geom1d::GetNodes(VecInt &nodes)
{
	nodes = fNodeIndices;
}

int Geom1d::NodeIndex(int node)
{
	return fNodeIndices[node];
}

GeoElementSide Geom1d::Neighbour(int side)
{
	return fNeighbours[side];
}

void Geom1d::SetNeighbour(int side, const GeoElementSide &neighbour)
{
	fNeighbours[side] = neighbour;
}