/*
*  Analysis.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "Analysis.h"
#include "Assemble.h"
#include "CompMesh.h"

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
	
	/*Matrix gk, gf;
	gf.Resize(4, 1); gf(0, 0) = RightHandSide(2, 0); gf(2, 0) = RightHandSide(6, 0);

	gk.Resize(4, 4);
	gk(0, 0) = GlobalSystem(2, 2); gk(0, 1) = GlobalSystem(2, 3); gk(0, 2) = GlobalSystem(2, 6); gk(0, 3) = GlobalSystem(2, 7);
	gk(1, 0) = GlobalSystem(3, 2); gk(1, 1) = GlobalSystem(3, 3); gk(1, 2) = GlobalSystem(3, 6); gk(1, 3) = GlobalSystem(3, 7);
	gk(2, 0) = GlobalSystem(6, 2); gk(2, 1) = GlobalSystem(6, 3); gk(2, 2) = GlobalSystem(6, 6); gk(2, 3) = GlobalSystem(6, 7);
	gk(3, 0) = GlobalSystem(7, 2); gk(3, 1) = GlobalSystem(7, 3); gk(3, 2) = GlobalSystem(7, 6); gk(3, 3) = GlobalSystem(7, 7);

	//gk.Print(std::cout);
	//gf.Print(std::cout);

	gk.Solve_LU(gf);
	RightHandSide.Zero();
	RightHandSide(2, 0) = gf(0, 0); RightHandSide(3, 0) = gf(1, 0); RightHandSide(6, 0) = gf(2, 0); RightHandSide(7, 0) = gf(3, 0);
	*/
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

void Analysis::PostProcessError(VecDouble error, std::ostream & out, PostProcess & defPostProc) const
{
}
