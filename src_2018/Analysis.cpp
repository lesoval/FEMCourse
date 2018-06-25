/*
*  Analysis.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "Analysis.h"
#include "Assemble.h"
#include "CompMesh.h"
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

	VecDouble sol(Solution.Rows());
	for (int i = 0; i < Solution.Rows(); i++)
	{
		sol[i] = Solution(i, 0);
	}
	
	cmesh->LoadSolution(sol);

	std::cout << " -> done!" << std::endl;
}

void Analysis::PostProcessSolution(const std::string & filename, PostProcess & defPostProc) const
{
}

VecDouble Analysis::PostProcessError(std::ostream & out, PostProcess & defPostProc) const
{
	return VecDouble();
}
