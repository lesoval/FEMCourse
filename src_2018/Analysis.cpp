/*
*  Analysis.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "Analysis.h"

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
}

void Analysis::PostProcessSolution(const std::string & filename, PostProcess & defPostProc) const
{
}

void Analysis::PostProcessError(VecDouble error, std::ostream & out, PostProcess & defPostProc) const
{
}
