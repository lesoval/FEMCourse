/*
*  CompMesh.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "CompMesh.h"
#include "GeoElement.h"
#include "GeoElementSide.h"
#include "GeoMesh.h"
#include "MathStatement.h"
#include "tpanic.h"

CompMesh::CompMesh() {}

CompMesh::CompMesh(GeoMesh * gmesh)
{
	SetGeoMesh(gmesh);
}

CompMesh::CompMesh(const CompMesh &copy)
{
	compelements = copy.compelements;
	dofs = copy.dofs;
	mathstatements = copy.mathstatements;
}

CompMesh::~CompMesh() {}

GeoMesh * CompMesh::GetGeoMesh() const
{
	return geomesh;
}

void CompMesh::SetGeoMesh(GeoMesh * gmesh)
{
	geomesh = gmesh;
}

void CompMesh::SetNumberElement(int64_t nelem)
{
	compelements.resize(nelem);
}

void CompMesh::SetNumberDOF(int64_t ndof)
{
	dofs.resize(ndof);
}

void CompMesh::SetNumberMath(int nmath)
{
	mathstatements.resize(nmath);
}

void CompMesh::SetElement(int64_t elindex, CompElement *cel)
{
	compelements[elindex] = cel;
}

void CompMesh::SetDOF(int64_t index, const DOF &dof)
{
	dofs[index] = dof;
}

void CompMesh::SetMathStatement(int index, MathStatement *math)
{
	mathstatements[index] = math;
}

DOF &CompMesh::GetDOF(int64_t dofindex)
{
	return dofs[dofindex];
}

CompElement *CompMesh::GetElement(int64_t elindex) const
{
	return compelements[elindex];
}

MathStatement *CompMesh::GetMath(int matindex) const
{
	return mathstatements[matindex];
}

std::vector<CompElement *> CompMesh::GetElementVec() const
{
	return compelements;
}

std::vector<DOF> CompMesh::GetDOFVec() const
{
	return dofs;
}

std::vector<MathStatement *> CompMesh::GetMathVec() const
{
	return mathstatements;
}

void CompMesh::SetElementVec(const std::vector<CompElement *> &vec)
{
	compelements = vec;
}

void CompMesh::SetDOFVec(const std::vector<DOF> &dofvec)
{
	dofs = dofvec;
}

void CompMesh::SetMathVec(const std::vector<MathStatement *> &mathvec)
{
	mathstatements = mathvec;
}

void CompMesh::AutoBuild()
{
	int nElements = geomesh->NumElements();
	int nMaths = mathstatements.size();

	SetNumberElement(nElements);

	for (int i = 0; i < nElements; i++)
	{
		//Cria e insere o elemento na malha computacional
		GeoElement *gel = geomesh->Element(i);
		CompElement *cel = gel->CreateCompEl(this, i);
		SetElement(i, cel);	

		int mat = gel->Material();
		//Insere a equação diferencial do elemento
		if (mat >= 0 && mat < nMaths)
		{
			cel->SetStatement(GetMath(mat));
		}
		else
		{
			std::cout << "CompMesh::AutoBuild --> Invalid material" << std::endl;
			DebugStop();
		}

		int nShapes = cel->NShapeFunctions();
		int nStates = cel->GetStatement()->NState();
		//Insere os indices dos DOF's nos nós do elemento
		for (int j = 0; j < nShapes; j++)
		{
			GeoElementSide gelside(gel, j);
			GeoElementSide neighbour = gel->Neighbour(j);
			int neighId = neighbour.Element()->GetIndex();

			if (gelside != neighbour)
			{
				if (neighId < i)
				{
					CompElement *cneigh = neighbour.Element()->GetReference();
					cel->SetDOFIndex(j, cneigh->GetDOFIndex(neighbour.Side()));
				}
				else
				{
					cel->SetDOFIndex(j, dofs.size());
					DOF cdof;
					cdof.SetNShapeStateOrder(cel->ComputeNShapeFunctions(j, DefaultOrder), nStates, DefaultOrder);
					dofs.push_back(cdof);
				}
			}
			else
			{
				cel->SetDOFIndex(j, dofs.size());
				DOF cdof;
				cdof.SetNShapeStateOrder(cel->ComputeNShapeFunctions(j, DefaultOrder), nStates, DefaultOrder);
				dofs.push_back(cdof);
			}
		}
	}
	this->Resequence();
}

void CompMesh::Resequence()
{
	int nDOF = GetNumberDOF();
	int firstEq = 0;

	for (int i = 0; i < nDOF; i++)
	{
		int nShapes = GetDOF(i).GetNShape();
		int nStates = GetDOF(i).GetNState();

		GetDOF(i).SetFirstEquation(firstEq);
		firstEq += nShapes * nStates;
	}
}

void CompMesh::Resequence(VecInt & DOFindices)
{
}

std::vector<double>& CompMesh::Solution()
{
	return solution;
}

void CompMesh::LoadSolution(std::vector<double>& Sol)
{
	solution = Sol;
}