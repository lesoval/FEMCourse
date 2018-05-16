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

GeomTetrahedron::GeomTetrahedron(const GeomTetrahedron &copy)
{
	this->operator =(copy);
}

GeomTetrahedron &GeomTetrahedron::operator=(const GeomTetrahedron &copy)
{
	fNodeIndices = copy.fNodeIndices;

	for (int i = 0; i<nSides; i++)
	{
		fNeighbours[i] = copy.fNeighbours[i];
	}

	return *this;
}

void GeomTetrahedron::Shape(const VecDouble &xi, VecDouble &phi, TMatrix &dphi)
{
	double ksi = xi[0];
	double eta = xi[1];
	double zeta = xi[2];

	phi[0] = 1 - ksi - eta - zeta;
	phi[1] = ksi;
	phi[2] = eta;
	phi[3] = zeta;

	dphi(0, 0) = -1;	dphi(1, 0) = -1;	dphi(2, 0) = -1;
	dphi(0, 1) = 1;		dphi(1, 1) = 0;		dphi(2, 1) = 0;
	dphi(0, 2) = 0;		dphi(1, 2) = 1;		dphi(2, 2) = 0;
	dphi(0, 3) = 0;		dphi(1, 3) = 0;		dphi(2, 3) = 1;
}

void GeomTetrahedron::X(const VecDouble &xi, TMatrix &NodeCo, VecDouble &x)
{
	int nRows = NodeCo.Rows();
	int nCols = NodeCo.Cols();

	VecDouble phi(4);
	TMatrix dphi(3, 4);
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

void GeomTetrahedron::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx)
{
	int nRows = NodeCo.Rows();
	int nCols = NodeCo.Cols();

	if (nCols != 4)
	{
		std::cout << "GeomTetrahedron::GradX --> Objects of incompatible lengths, gradient cannot be computed." << std::endl;
		std::cout << "Nodes matrix must be 3x4." << std::endl;
		DebugStop();
	}

	gradx.Resize(nRows, 3);
	gradx.Zero();

	VecDouble phi(4);
	TMatrix dphi(3, 4);
	Shape(xi, phi, dphi);

	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0; j < nRows; j++)
		{
			gradx(j, 0) += NodeCo.GetVal(j, i)*dphi(0, i);
			gradx(j, 1) += NodeCo.GetVal(j, i)*dphi(1, i);
			gradx(j, 2) += NodeCo.GetVal(j, i)*dphi(2, i);
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

void GeomTetrahedron::SetNeighbour(int side, const GeoElementSide &neighbour)
{
	fNeighbours[side] = neighbour;
}