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

int Restrain::VariableIndex(const PostProcVar var) const
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

Restrain::PostProcVar Restrain::VariableIndex(const std::string & name)
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

int Restrain::NSolutionVariables(const PostProcVar var)
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

void Restrain::PostProcessSolution(const IntPointData & integrationpointdata, const int var, VecDouble & sol) const
{
}