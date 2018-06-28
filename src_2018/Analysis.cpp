/*
*  Analysis.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "Analysis.h"
#include "Assemble.h"
#include "CompMesh.h"
#include "CompElement.h"
#include "MathStatement.h"
#include "VTKGeoMesh.h"
#include <fstream>

Analysis::Analysis()
{
}

Analysis::Analysis(const Analysis & cp)
{
	this->operator=(cp);
}

Analysis & Analysis::operator=(const Analysis & cp)
{
	cmesh = cp.cmesh;
	Solution = cp.Solution;
	GlobalSystem = cp.GlobalSystem;
	RightHandSide = cp.RightHandSide;

	return *this;
}

Analysis::~Analysis()
{
}

Analysis::Analysis(CompMesh * cmesh)
{
	SetMesh(cmesh);
}

void Analysis::SetMesh(CompMesh * cmesh)
{
	this->cmesh = cmesh;
}

CompMesh * Analysis::Mesh() const
{
	return cmesh;
}

void Analysis::RunSimulation()
{
	Assemble assem(cmesh);
	std::cout << "Assemble";
	assem.Compute(GlobalSystem, RightHandSide);
	std::cout << " -> done!" << std::endl;

	//std::ofstream out("matrizes.txt");
	//GlobalSystem.Print(out << std::endl);
	//RightHandSide.Print(out << std::endl);
	
	Matrix EK = GlobalSystem;
	Solution = RightHandSide;

	std::cout << "Run Simulation";
	EK.Solve_LU(Solution);
	//Solution.Print(out << std::endl);

	VecDouble sol = Solution.GetCol(0);
	cmesh->LoadSolution(sol);

	std::cout << " -> done!" << std::endl;
}

void Analysis::PostProcessSolution(const std::string & filename, PostProcess & defPostProc) const
{
	VTKGeoMesh::PrintSolVTK(cmesh, defPostProc, "S" + filename + ".vtk");
}

VecDouble Analysis::PostProcessError(std::ostream & out, PostProcess & defPostProc) const
{
	VecDouble tError(3);
	int nElements = cmesh->GetElementVec().size();

	for (int i = 0; i < nElements; i++)
	{
		CompElement *cel = cmesh->GetElement(i);
		int nErrors = cel->GetStatement()->NEvalErrors();

		VecDouble errors(nErrors);
		cel->EvaluateError(defPostProc.GetExact(), errors);

		for (int j = 0; j < nErrors; j++)
		{
			tError[j] += errors[j];
		}
	}

	for (int i = 0; i < tError.size(); i++)
	{
		tError[i] = sqrt(tError[i]);
	}

	out << "Error -> u = " << tError[0] << std::endl;
	out << "Error -> Grad u = " << tError[1] << std::endl;
	out << "Error -> u + Grad u = " << tError[2] << std::endl;

	return tError;
}
