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
	SolutionExact = copy.SolutionExact;

	return *this;
}

PlaneStrainShell::~PlaneStrainShell()
{
}

PlaneStrainShell * PlaneStrainShell::Clone() const
{
	return new PlaneStrainShell(*this);
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

int PlaneStrainShell::VariableIndex(const PostProcVar var) const
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
	case EError:
		return 7;
	case EDError:
		return 8;
	default:
		std::cout << " Variable not implemented " << std::endl;
		DebugStop();
		break;
	}
}

PlaneStrainShell::PostProcVar PlaneStrainShell::VariableIndex(const std::string & name)
{
	if (!strcmp("Displacement", name.c_str()))	return ESol;
	if (!strcmp("Strain", name.c_str()))		return EDSol;
	if (!strcmp("Tension", name.c_str()))		return EFlux;
	if (!strcmp("Force", name.c_str()))			return EForce;
	if (!strcmp("SolExact", name.c_str()))		return ESolExact;
	if (!strcmp("DSolExact", name.c_str()))		return EDSolExact;
	if (!strcmp("Error", name.c_str()))			return EError;
	if (!strcmp("DError", name.c_str()))		return EDError;
	else
	{
		std::cout << " Variable not implemented " << std::endl;
		DebugStop();
		return ENone;
	}
}

int PlaneStrainShell::NSolutionVariables(const PostProcVar var)
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
	case EError:
		return 3;
	case EDError:
		return 3;
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
	Matrix dsoldx = integrationpointdata.dsoldx;
	Matrix axes = integrationpointdata.axes;
	double weight = integrationpointdata.weight;
	double detjac = integrationpointdata.detjac;

	int nStates = NState();
	int dim = Dimension();

	Matrix dsol;
	Axes2XYZ(dsoldx, dsol, axes);

	for (int i = 0; i < nStates; i++)
	{
		errors[0] += pow(sol[i] - u_exact[i], 2) * weight*detjac;
	}

	for (int i = 0; i < nStates; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			errors[1] += pow(dsol(i, i) - du_exact(i, 0), 2)*weight*detjac;
		}
	}

	errors[2] = errors[0] + errors[1];
}

void PlaneStrainShell::PostProcessSolution(const IntPointData & integrationpointdata, const int var, VecDouble & sol) const
{
	PostProcVar Var = PostProcVar(var);
	VecDouble  x = integrationpointdata.x;
	VecDouble solution = integrationpointdata.solution;
	Matrix dsoldx = integrationpointdata.dsoldx;
	Matrix axes = integrationpointdata.axes;

	Matrix gradsol;
	Axes2XYZ(dsoldx, gradsol, axes);

	switch (Var)
	{
	case PlaneStrainShell::ESol:
		sol = solution;
		break;
	case PlaneStrainShell::EDSol:
	{
		sol.resize(3);

		sol[0] = gradsol(0, 0);
		sol[1] = gradsol(1, 1);
		sol[2] = gradsol(0, 1) + gradsol(1, 0);
	}
	break;
	case PlaneStrainShell::EFlux:
	{
		VecDouble dsol(3);
		Matrix C = GetConstitutive();

		dsol[0] = gradsol(0, 0);
		dsol[1] = gradsol(1, 1);
		dsol[2] = gradsol(0, 1) + gradsol(1, 0);

		sol = C * dsol;
	}
	break;
	case PlaneStrainShell::EForce:
		if (forceFunction != NULL)
		{
			VecDouble force(NState());
			forceFunction(x, force);
			force.push_back(0);

			sol = force;
		}
		break;
	case PlaneStrainShell::ESolExact:
	{
		VecDouble sol_exact;
		Matrix dsol_exact;
		SolutionExact(x, sol_exact, dsol_exact);

		sol = sol_exact;
	}
		break;
	case PlaneStrainShell::EDSolExact:
	{
		VecDouble sol_exact;
		Matrix dsol_exact;
		SolutionExact(x, sol_exact, dsol_exact);

		sol = dsol_exact.GetCol(0);
	}
		break;
	case PlaneStrainShell::EError:
	{
		VecDouble sol_exact;
		Matrix dsol_exact;
		SolutionExact(x, sol_exact, dsol_exact);

		sol.resize(3);

		for (int i = 0; i < 2; i++)
		{
			sol[i] = abs(sol_exact[i] - solution[i]);
		}
	}
	break;
	case PlaneStrainShell::EDError:
	{
		VecDouble sol_exact;
		Matrix dsol_exact;
		SolutionExact(x, sol_exact, dsol_exact);

		sol.resize(3);
		VecDouble dsol(3);
		dsol[0] = gradsol(0, 0);
		dsol[1] = gradsol(1, 1);
		dsol[2] = gradsol(0, 1) + gradsol(1, 0);

		for (int i = 0; i < 3; i++)
		{
			sol[i] = abs(dsol_exact.GetCol(0)[i] - dsol[i]);
		}
	}
	break;
	default:
		std::cout << " Variable index not implemented " << std::endl;
		DebugStop();
		break;
	}
}
