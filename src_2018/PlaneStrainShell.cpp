/*
*  PlaneStrainShell.cpp
*
*  Created by Leandro Valdez on 6/24/18.
*
*/

#include "PlaneStrainShell.h"

PlaneStrainShell::PlaneStrainShell()
{
}

PlaneStrainShell::PlaneStrainShell(int materialid, double E, double ni, double thickness)
{
	SetMatID(materialid);
	cMat = Constitutive(E, ni);
	t = thickness;
}

PlaneStrainShell::PlaneStrainShell(const PlaneStrainShell & copy)
{
	this->operator=(copy);
}

PlaneStrainShell & PlaneStrainShell::operator=(const PlaneStrainShell & copy)
{
	cMat = copy.cMat;
	forceFunction = copy.forceFunction;

	return *this;
}

PlaneStrainShell * PlaneStrainShell::Clone() const
{
	return new PlaneStrainShell(*this);
}

PlaneStrainShell::~PlaneStrainShell()
{
}

Matrix PlaneStrainShell::Constitutive(double E, double ni)
{
	Matrix m(3, 3);

	m(0, 0) = 1 - ni;	m(0, 1) = ni;		m(0, 2) = 0;
	m(1, 0) = ni;		m(1, 1) = 1 - ni;	m(1, 2) = 0;
	m(2, 0) = 0;		m(2, 1) = 0;		m(2, 2) = (1 - 2 * ni) / 2;

	Matrix c(3, 3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			c(i, j) = (E / (1 + ni)*(1 - 2 * ni))*m(i, j);
		}
	}
	return c;
}

Matrix PlaneStrainShell::GetConstitutive() const
{
	return cMat;
}

int PlaneStrainShell::NEvalErrors() const
{
	return 3;
}

int PlaneStrainShell::NState() const
{
	return 2;
}

int PlaneStrainShell::VariableIndex(const std::string & name)
{
	return 0;
}

int PlaneStrainShell::NSolutionVariables(const PostProcVar var)
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

void PlaneStrainShell::Contribute(IntPointData & intpointdata, double weight, Matrix & EK, Matrix & EF) const
{
	VecDouble &phi = intpointdata.phi;
	Matrix &dphidx = intpointdata.dphidx;
	VecDouble  &x = intpointdata.x;
	Matrix  &axes = intpointdata.axes;
	double detjac = intpointdata.detjac;

	int nStates = NState();
	int nShapes = intpointdata.phi.size();

	if (forceFunction != NULL)
	{
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

	Matrix gradphi;
	Axes2XYZ(dphidx, gradphi, axes);

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

	Matrix ek = Bt * C * B *weight* detjac * t;
	EK = EK + ek;
}

void PlaneStrainShell::ContributeError(IntPointData & integrationpointdata, VecDouble & u_exact, Matrix & du_exact, VecDouble & errors) const
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

std::vector<double> PlaneStrainShell::PostProcessSolution(const IntPointData & integrationpointdata, const int var) const
{
	return std::vector<double>();
}
