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

int OnlyForce::VariableIndex(const PostProcVar var) const
{
	switch (var)
	{
	case ESol:
		return 1;
	case EDSol:
		return 2;
	case EFlux:
		return 3;
	case EForce:
		return 4;
	case ESolExact:
		return 5;
	case EDSolExact:
		return 6;
	default:
		std::cout << " Variable not implemented " << std::endl;
		DebugStop();
		break;
	}
}

OnlyForce::PostProcVar OnlyForce::VariableIndex(const std::string & name)
{
	if (!strcmp("Displacement", name.c_str()))	return ESol;
	if (!strcmp("Strain", name.c_str()))		return EDSol;
	if (!strcmp("Tension", name.c_str()))		return EFlux;
	if (!strcmp("Force", name.c_str()))			return EForce;
	if (!strcmp("SolExact", name.c_str()))		return ESolExact;
	if (!strcmp("DSolExact", name.c_str()))		return EDSolExact;
	else
	{
		std::cout << " Variable not implemented " << std::endl;
		DebugStop();
		return ENone;
	}
}

int OnlyForce::NSolutionVariables(const PostProcVar var)
{
	switch (var)
	{
	case ESol:
		return NState();
	case EDSol:
		return 3;
	case EFlux:
		return 3;
	case EForce:
		return NState();
	case ESolExact:
		return NState();
	case EDSolExact:
		return 3;
	default:
		std::cout << " Variable not implemented " << std::endl;
		DebugStop();
		break;
	}
}

void OnlyForce::Contribute(IntPointData & intpointdata, double weight, Matrix & EK, Matrix & EF) const
{
	if (forceFunction != NULL)
	{
		VecDouble &phi = intpointdata.phi;
		Matrix axes = intpointdata.axes;
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
}

void OnlyForce::ContributeError(IntPointData & integrationpointdata, VecDouble & u_exact, Matrix & du_exact, VecDouble & errors) const
{
}

void OnlyForce::PostProcessSolution(const IntPointData & integrationpointdata, const int var, VecDouble & sol) const
{
}