/*
*  Restrain.cpp
*
*  Created by Leandro Valdez on 6/11/18.
*
*/

#include "Restrain.h"

Restrain::Restrain()
{
}

Restrain::Restrain(int materialid)
{
	SetMatID(materialid);
}

Restrain::Restrain(const Restrain & copy)
{
	this->operator=(copy);
}

Restrain & Restrain::operator=(const Restrain & copy)
{
	forceFunction = copy.forceFunction;

	return *this;
}

Restrain * Restrain::Clone() const
{
	return new Restrain(*this);
}

Restrain::~Restrain()
{
}

int Restrain::NEvalErrors() const
{
	return 0;
}

int Restrain::NState() const
{
	return 2;
}

void Restrain::Contribute(IntPointData & intpointdata, double weight, Matrix & EK, Matrix & EF) const
{
	VecDouble &phi = intpointdata.phi;
	VecDouble  &x = intpointdata.x;
	double detjac = intpointdata.detjac;

	int nStates = NState();
	int nShapes = intpointdata.phi.size();

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < nStates; j++)
		{
			EK(nStates*i + j, nStates*i + j) += gBigNumber * phi[i] * phi[i] * detjac*weight;
		}
	}
}

void Restrain::ContributeError(IntPointData & integrationpointdata, VecDouble & u_exact, Matrix & du_exact, VecDouble & errors) const
{
}

std::vector<double> Restrain::PostProcessSolution(const IntPointData & integrationpointdata, const int var) const
{
	return std::vector<double>();
}
