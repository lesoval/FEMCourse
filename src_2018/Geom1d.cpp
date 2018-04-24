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

Geom1d::Geom1d(const Geom1d &copy) :fNodeIndices(copy.fNodeIndices) {}

Geom1d &Geom1d::operator=(const Geom1d &copy)
{
	return *this;
}

void Geom1d::Shape(const VecDouble &xi, VecDouble &phi, TMatrix &dphi)
{
	phi[0] = (1 - xi[0]) / 2;
	phi[1] = (1 + xi[0]) / 2;

	dphi.PutVal(0, 0, -0.5);
	dphi.PutVal(0, 1, 0.5);
}

void Geom1d::X(const VecDouble &xi, TMatrix &NodeCo, VecDouble &x)
{
	for (int i = 0; i < NodeCo.Rows(); i++)
	{
		x[i] = NodeCo.GetVal(i, 0)*(1 - xi[i]) / 2 + NodeCo.GetVal(i, 1)*(1 + xi[i]) / 2;
	}
}

void Geom1d::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx)
{
	gradx.Resize(NodeCo.Rows(), 1);
	gradx.Zero();

	VecDouble phi(2);
	TMatrix dphi(2, 2);
	Shape(xi, phi, dphi);

	for (int i = 0; i < NodeCo.Cols(); i++)
	{
		for (int j = 0; j < NodeCo.Rows(); j++)
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