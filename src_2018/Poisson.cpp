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

int Poisson::VariableIndex(const PostProcVar var) const
{
	return 0;
}

Poisson::PostProcVar Poisson::VariableIndex(const std::string & name)
{
	return PostProcVar();
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

	int nStates = NState();
	int nShapes = integrationpointdata.phi.size();

	VecDouble force(nStates);
	forceFunction(x, force);

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < nStates; j++)
		{
			EF(nStates*i + j, 0) += detjac * weight * phi[i] * force[j];
		}
	}

	Matrix gradphi(nStates, nShapes);

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < nStates; j++)
		{
			for (int k = 0; k < nStates; k++)
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
			for (int k = 0; k < nStates; k++)
			{
				for (int l = 0; l < nStates; l++)
				{
					for (int m = 0; m < nStates; m++)
					{
						EK(nStates*i + k, nStates*j + l) += detjac * weight*(gradphi(k, i)*gradphi(m, j))*perm(m, l);
					}
				}
			}
		}
	}
}

void Poisson::ContributeError(IntPointData & integrationpointdata, VecDouble & u_exact, Matrix & du_exact, VecDouble & errors) const
{
	VecDouble sol = integrationpointdata.solution;
	Matrix dsol = integrationpointdata.dsoldx;
	double weight = integrationpointdata.weight;
	double detjac = integrationpointdata.detjac;

	int nStates = NState();
	int dim = Dimension();

	for (int i = 0; i < nStates; i++)
	{
		errors[0] += pow(sol[i] - u_exact[i], 2) * weight*detjac;
	}

	for (int i = 0; i < nStates; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			errors[1] += pow(dsol(i, j) - du_exact(i, j), 2)*weight*detjac;
		}
	}

	errors[2] = errors[1] + errors[2];
}

std::vector<double> Poisson::PostProcessSolution(const IntPointData & integrationpointdata, const int var) const
{
	return std::vector<double>();
}

double Poisson::Inner(Matrix & S, Matrix & T) const
{
	return 0.0;
}
