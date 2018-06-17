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

	
	assem.Compute(GlobalSystem, RightHandSide);
	//GlobalSystem.Print(std::cout);
	//RightHandSide.Print(std::cout);
	
	Solution = RightHandSide;

	std::cout << "Running Simulation..." << std::endl;
	GlobalSystem.Solve_LU(Solution);
	//Solution.Print(std::cout);
	VecDouble sol(Solution.Rows());
	for (int i = 0; i < Solution.Rows(); i++)
	{
		sol[i] = Solution(i, 0);
	}

	cmesh->LoadSolution(sol);

	std::cout << "Simulation Finished" << std::endl;
}

void Analysis::PostProcessSolution(const std::string & filename, PostProcess & defPostProc) const
{
}

VecDouble Analysis::PostProcessError(std::ostream & out, PostProcess & defPostProc) const
{
	return VecDouble();
}
