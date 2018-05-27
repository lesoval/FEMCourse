/*
*  Assemble.cpp
*
*  Created by Leandro Valdez on 5/24/18.
*
*/

#include "Assemble.h"
#include "CompMesh.h"
#include "CompElement.h"
#include "GeoElement.h"
#include "GeoElementTemplate.h"

Assemble::Assemble()
{
}

Assemble::Assemble(CompMesh * mesh)
{
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
	return int64_t();
}

void Assemble::OptimizeBandwidth()
{
}

void Assemble::Compute(Matrix & globmat, Matrix & rhs)
{
}
