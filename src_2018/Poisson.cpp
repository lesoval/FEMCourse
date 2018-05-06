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
	//forceFunction = copy.forceFunction;

	return *this;
}

Poisson * Poisson::Clone() const
{
	
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
	return 0;
}

void Poisson::Contribute(IntPointData & integrationpointdata, Matrix & EK, Matrix & EF) const
{

}

void Poisson::PostProcess(IntPointData & integrationpointdata, const std::string & variable, VecDouble & postprocvalue) const
{

}
