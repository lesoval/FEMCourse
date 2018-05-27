/*
*  Poisson.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "Poisson.h"

Poisson::Poisson() {}

Poisson::Poisson(Matrix & perm)
{
	permeability = perm;
}

Poisson::Poisson(const Poisson & copy)
{
	this->operator=(copy);
}

Poisson & Poisson::operator=(const Poisson & copy)
{
	permeability = copy.permeability;
	forceFunction = copy.forceFunction;

	return *this;
}

Poisson * Poisson::Clone() const
{
	return new Poisson(*this);
}

Poisson::~Poisson() {}

Matrix Poisson::GetPermeability() const
{
	return permeability;
}

void Poisson::SetPermeability(const Matrix & perm)
{
	permeability = perm;
}

int Poisson::NState() const
{
	return 1;
}

void Poisson::Contribute(IntPointData &integrationpointdata, double weight, Matrix &EK, Matrix &EF) const
{
	VecDouble &phi = integrationpointdata.phi;
	Matrix &dphix = integrationpointdata.dphidx;
	VecDouble  &x = integrationpointdata.x;
	Matrix  &axes = integrationpointdata.axes;
	double detjac = integrationpointdata.detjac;

	int dim = integrationpointdata.x.size();
	int nShapes = integrationpointdata.phi.size();

	VecDouble force(dim);
	forceFunction(x, force);

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			EF(i, j) += detjac * weight * phi[i] * force[j];
		}
	}

	Matrix perm = permeability;
	Matrix gradphi(dim, nShapes);

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			for (int k = 0; k < dim; k++)
			{
				gradphi(k, i) += dphix(j, i)*axes(j, k);
			}
		}
	}

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < nShapes; j++)
		{
			for (int k = 0; k < dim; k++)
			{
				EK(i, j) += detjac * weight*(gradphi(k, i)*gradphi(k, j));
			}
		}
	}	
}

std::vector<double> Poisson::PostProcess(const IntPointData & integrationpointdata, const PostProcVar var) const
{
	return std::vector<double>();
}
