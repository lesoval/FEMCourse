/*
*  GeomTriangle.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeomTriangle.h"
#include "tpanic.h"

GeomTriangle::GeomTriangle() {}

GeomTriangle::~GeomTriangle() {}

GeomTriangle::GeomTriangle(const GeomTriangle &copy)
{
	this->operator =(copy);
}

GeomTriangle &GeomTriangle::operator=(const GeomTriangle &copy)
{
	fNodeIndices = copy.fNodeIndices;

	for (int i = 0; i<nSides; i++)
	{
		fNeighbours[i] = copy.fNeighbours[i];
	}

	return *this;
}

void GeomTriangle::Shape(const VecDouble &xi, VecDouble &phi, TMatrix &dphi)
{
	double ksi = xi[0];
	double eta = xi[1];

	phi[0] = 1 - ksi - eta;
	phi[1] = ksi;
	phi[2] = eta;

	dphi(0, 0) = -1;	dphi(1, 0) = -1;
	dphi(0, 1) = 1;		dphi(1, 1) = 0;
	dphi(0, 2) = 0;		dphi(1, 2) = 1;
}

void GeomTriangle::X(const VecDouble &xi, TMatrix &NodeCo, VecDouble &x)
{
	int nRows = NodeCo.Rows();
	int nCols = NodeCo.Cols();

	VecDouble phi(3);
	TMatrix dphi(2, 3);
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

void GeomTriangle::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx)
{
	int nRows = NodeCo.Rows();
	int nCols = NodeCo.Cols();

	if (nCols != 3)
	{
		std::cout << "GeomTriangle::GradX --> Objects of incompatible lengths, gradient cannot be computed." << std::endl;
		std::cout << "Nodes matrix must be spacex3." << std::endl;
		DebugStop();
	}

	gradx.Resize(NodeCo.Rows(), 2);
	gradx.Zero();

	VecDouble phi(3);
	TMatrix dphi(2, 3);
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

int GeomTriangle::NumNodes()
{
	return nCorners;
}

void GeomTriangle::SetNodes(const VecInt &nodes)
{
	fNodeIndices = nodes;
}

void GeomTriangle::GetNodes(VecInt &nodes)
{
	nodes = fNodeIndices;
}

int GeomTriangle::NodeIndex(int node)
{
	return fNodeIndices[node];
}

GeoElementSide GeomTriangle::Neighbour(int side)
{
	return fNeighbours[side];
}

void GeomTriangle::SetNeighbour(int side, GeoElementSide &neighbour)
{
	fNeighbours[side] = neighbour;
}