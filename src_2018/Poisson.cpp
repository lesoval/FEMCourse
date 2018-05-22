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
	Matrix &dphi = integrationpointdata.dphidx;
	VecDouble &x = integrationpointdata.x;
	Matrix &axes = integrationpointdata.axes;

	int nphi = phi.size();
	//     VecDouble f(1,0.); incluir set force function no main
	//     forceFunction(x,f);
	Matrix perm = GetPermeability();
	Matrix Kdphi(2, 2, 0.);

	for (int ik = 0; ik<2; ik++)
	{
		for (int jk = 0; jk<2; jk++)
		{
			for (int kd = 0; kd<2; kd++)
			{
				Kdphi(ik, jk) += perm(ik, kd)*dphi(kd, jk);
			}
		}
	}

	for (int in = 0; in<2; in++)
	{
		EF(in, 0) += -weight * phi[in] * 0;
		for (int jn = 0; jn<nphi; jn++)
		{
			for (int kd = 0; kd<2; kd++)
			{
				EK(in, jn) += weight * (Kdphi(kd, in)*dphi(kd, jn));
			}
		}
	}
}

std::vector<double> Poisson::PostProcess(const IntPointData & integrationpointdata, const PostProcVar var) const
{
	return std::vector<double>();
}
