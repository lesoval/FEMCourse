/*
*  PlaneStressShell.cpp
*
*  Created by Leandro Valdez on 6/11/18.
*
*/

#include "PlaneStressShell.h"

PlaneStressShell::PlaneStressShell()
{
}

PlaneStressShell::PlaneStressShell(int materialid, double E, double ni, double thickness)
{
	SetMatID(materialid);
	cMat = Constitutive(E, ni);
	t = thickness;
}

PlaneStressShell::PlaneStressShell(const PlaneStressShell & copy)
{
	this->operator=(copy);
}

PlaneStressShell & PlaneStressShell::operator=(const PlaneStressShell & copy)
{
	cMat = copy.cMat;
	forceFunction = copy.forceFunction;

	return *this;
}

PlaneStressShell * PlaneStressShell::Clone() const
{
	return new PlaneStressShell(*this);
}

PlaneStressShell::~PlaneStressShell()
{
}

Matrix PlaneStressShell::Constitutive(double E, double ni)
{
	Matrix m(3, 3);

	m(0, 0) = 1;	m(0, 1) = ni;	m(0, 2) = 0;
	m(1, 0) = ni;	m(1, 1) = 1;	m(1, 2) = 0;
	m(2, 0) = 0;	m(2, 1) = 0;	m(2, 2) = (1 - ni) / 2;

	Matrix c(3, 3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			c(i, j) = (E / (1 - ni * ni))*m(i, j);
		}
	}
	return c;
}

Matrix PlaneStressShell::GetConstitutive() const
{
	return cMat;
}

int PlaneStressShell::NEvalErrors() const
{
	return 0;
}

int PlaneStressShell::NState() const
{
	return 2;
}

int PlaneStressShell::VariableIndex(const std::string & name)
{
	return 0;
}

int PlaneStressShell::NSolutionVariables(const PostProcVar var)
{
	switch (var)
	{
	case ESol:
		return NState();
	case EDSol:
		return Dimension()*NState();
	case ETension:
		return Dimension()*NState();
	case EForce:
		return NState();
	case ESolExact:
		return NState();
	case EDSolExact:
		return Dimension()*NState();
	default:
		std::cout << " Variable not implemented " << std::endl;
		DebugStop();
		break;
	}
}

void PlaneStressShell::Contribute(IntPointData & intpointdata, double weight, Matrix & EK, Matrix & EF) const
{
	VecDouble &phi = intpointdata.phi;
	Matrix &dphidx = intpointdata.dphidx;
	VecDouble  &x = intpointdata.x;
	Matrix  &axes = intpointdata.axes;
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
	
	Matrix B(3, nShapes*nStates);

	for (int j = 0; j < nShapes; j++)
	{
		B(0, nStates*j) = gradphi(0, j);
		B(1, nStates*j + 1) = gradphi(1, j);
		B(2, nStates*j) = gradphi(1, j);
		B(2, nStates*j + 1) = gradphi(0, j);
	}

	Matrix Bt = B;
	Bt.Transpose();
	Matrix C = GetConstitutive();

	EK = Bt * C * B* weight* detjac * t;
}

void PlaneStressShell::ContributeError(IntPointData & integrationpointdata, VecDouble & u_exact, Matrix & du_exact, VecDouble & errors) const
{
}

std::vector<double> PlaneStressShell::PostProcessSolution(const IntPointData & integrationpointdata, const int var) const
{
	return std::vector<double>();
}
