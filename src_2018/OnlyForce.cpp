/*
*  OnlyForce.cpp
*
*  Created by Leandro Valdez on 6/11/18.
*
*/

#include "OnlyForce.h"

OnlyForce::OnlyForce()
{
}

OnlyForce::OnlyForce(int materialid)
{
	SetMatID(materialid);
}

OnlyForce::OnlyForce(const OnlyForce & copy)
{
	this->operator=(copy);
}

OnlyForce & OnlyForce::operator=(const OnlyForce & copy)
{
	forceFunction = copy.forceFunction;

	return *this;
}

OnlyForce * OnlyForce::Clone() const
{
	return new OnlyForce(*this);
}

OnlyForce::~OnlyForce()
{
}

int OnlyForce::NEvalErrors() const
{
	return 0;
}

int OnlyForce::NState() const
{
	return 2;
}

void OnlyForce::Contribute(IntPointData & intpointdata, double weight, Matrix & EK, Matrix & EF) const
{
	VecDouble &phi = intpointdata.phi;
	VecDouble  &x = intpointdata.x;
	double detjac = intpointdata.detjac;

	int nStates = NState();
	int nShapes = intpointdata.phi.size();

	VecDouble force(nStates);
	forceFunction(x, force);

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < nStates; j++)
		{
			EF(nStates*i + j, 0) += detjac * weight * phi[i] * force[j];
		}
	}
}

void OnlyForce::ContributeError(IntPointData & integrationpointdata, VecDouble & u_exact, Matrix & du_exact, VecDouble & errors) const
{
}

std::vector<double> OnlyForce::PostProcessSolution(const IntPointData & integrationpointdata, const int var) const
{
	return std::vector<double>();
}
