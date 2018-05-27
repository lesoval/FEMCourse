/*
*  CompMesh.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "CompMesh.h"
#include "GeoElement.h"
#include "MathStatement.h"

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
	int nNodes = geomesh->NumNodes();
	int nElements = geomesh->NumElements();

	SetNumberElement(nElements);
	SetNumberMath(nElements);
	SetNumberDOF(nNodes);

	for (int i = 0; i < nElements; i++)
	{
		GeoElement *gel = geomesh->Element(i);
		CompElement *CompEl = gel->CreateCompEl(this, i);
		SetElement(i, CompEl);	

		MathStatement *mat = GetMath(i);
		CompEl->SetStatement(mat);
	}
}

void CompMesh::Resequence()
{
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