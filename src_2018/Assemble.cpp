/*
*  Assemble.cpp
*
*  Created by Leandro Valdez on 5/24/18.
*
*/

#include "Assemble.h"
#include "CompMesh.h"
#include "CompElement.h"
#include "MathStatement.h"
#include "GeoElement.h"
#include "GeoElementTemplate.h"

Assemble::Assemble()
{
	cmesh = new CompMesh();
}

Assemble::Assemble(CompMesh * mesh)
{
	SetMesh(mesh);
}

Assemble::Assemble(const Assemble & copy)
{
	this->operator=(copy);
}

Assemble & Assemble::operator=(const Assemble & copy)
{
	cmesh = copy.cmesh;

	return *this;
}

void Assemble::SetMesh(CompMesh * cmesh)
{
	this->cmesh = cmesh;
}

int64_t Assemble::NEquations()
{
	int nDOF = cmesh->GetNumberDOF();
	int64_t nEquations = 0;

	for (int i = 0; i < nDOF; i++)
	{
		int64_t nShapes = cmesh->GetDOF(i).GetNShape();
		int64_t nStates = cmesh->GetDOF(i).GetNState();

		nEquations += nShapes * nStates;
	}
	return nEquations;
}

void Assemble::OptimizeBandwidth()
{
}

void Assemble::Compute(Matrix & globmat, Matrix & rhs)
{
	int nElements = cmesh->GetElementVec().size();
	int nEquations = NEquations();
	
	globmat.Resize(nEquations, nEquations);
	rhs.Resize(nEquations, 1);	

	for (int i = 0; i < nElements; i++)
	{
		CompElement *cel = cmesh->GetElement(i);
		int nShapes = cel->NShapeFunctions();
		int nStates = cel->GetStatement()->NState();

		Matrix ek, ef;
		cel->CalcStiff(ek, ef);

		VecInt firstEq(nShapes*nStates);

		for (int j = 0; j < nShapes; j++)
		{
			int dofId = cel->GetDOFIndex(j);
			DOF elDOF = cmesh->GetDOF(dofId);

			for (int k = 0; k < nStates; k++)
			{
				firstEq[nStates*j + k] = elDOF.GetFirstEquation() + k;
			}
		}

		for (int j = 0; j < nShapes*nStates; j++)
		{
			rhs(firstEq[j], 0) = ef(j, 0);

			for (int k = 0; k < nShapes*nStates; k++)
			{
				globmat(firstEq[j], firstEq[k]) += ek(j, k);
			}
		}
	}
}
