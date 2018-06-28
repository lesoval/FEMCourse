/*
*  L2Projection.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "L2Projection.h"

L2Projection::L2Projection() {}

L2Projection::L2Projection(int bctype, int materialid, Matrix & proj, Matrix Val1, Matrix Val2)
{
}

L2Projection::L2Projection(const L2Projection &copy)
{
	this->operator=(copy);
}

L2Projection &L2Projection::operator=(const L2Projection &copy)
{
	projection = copy.projection;
	forceFunction = copy.forceFunction;
	
	return *this;
}

L2Projection *L2Projection::Clone() const
{
	return 0;
}

L2Projection::~L2Projection() {}

Matrix L2Projection::GetProjectionMatrix() const
{
	return projection;
}

void L2Projection::SetProjectionMatrix(const Matrix &proj)
{
	projection = proj;
}

int L2Projection::NEvalErrors() const
{
	return 0;
}

int L2Projection::VariableIndex(const PostProcVar var) const
{
	return 0;
}

L2Projection::PostProcVar L2Projection::VariableIndex(const std::string & name)
{
	return PostProcVar();
}

int L2Projection::NSolutionVariables(const PostProcVar var)
{
	return 0;
}

void L2Projection::Contribute(IntPointData &integrationpointdata, double weight, Matrix &EK, Matrix &EF) const
{
}

void L2Projection::ContributeError(IntPointData & integrationpointdata, VecDouble & u_exact, Matrix & du_exact, VecDouble & errors) const
{
}

void L2Projection::PostProcessSolution(const IntPointData & integrationpointdata, const int var, VecDouble & sol) const
{
}
