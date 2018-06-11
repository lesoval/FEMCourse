/*
*  Poisson.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "Poisson.h"

Poisson::Poisson() {}

Poisson::Poisson(int materialid, Matrix & perm)
{
	SetMatID(materialid);
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

int Poisson::NEvalErrors() const
{
	return 0;
}

int Poisson::NState() const
{
	return 2;
}

int Poisson::VariableIndex(const std::string & name)
{
	return 0;
}

int Poisson::NSolutionVariables(const PostProcVar var)
{
	return 0;
}

void Poisson::Contribute(IntPointData &integrationpointdata, double weight, Matrix &EK, Matrix &EF) const
{
	VecDouble &phi = integrationpointdata.phi;
	Matrix &dphidx = integrationpointdata.dphidx;
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
			EF(dim*i + j, 0) += detjac * weight * phi[i] * force[j];
		}
	}

	Matrix gradphi(dim, nShapes);

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			for (int k = 0; k < dim; k++)
			{
				gradphi(k, i) += dphidx(j, i)*axes(j, k);
			}
		}
	}

	Matrix perm = permeability;

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < nShapes; j++)
		{
			for (int k = 0; k < dim; k++)
			{
				for (int l = 0; l < dim; l++)
				{
					for (int m = 0; m < dim; m++)
					{
						EK(dim*i + k, dim*j + l) += detjac * weight*(gradphi(k, i)*gradphi(m, j))*perm(m, l);
					}
				}
			}
		}
	}
}

void Poisson::ContributeError(IntPointData & integrationpointdata, VecDouble & u_exact, Matrix & du_exact, VecDouble & errors) const
{
}

std::vector<double> Poisson::PostProcessSolution(const IntPointData & integrationpointdata, const PostProcVar var) const
{
	return std::vector<double>();
}
