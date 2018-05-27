/*
*  L2Projection.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "L2Projection.h"

L2Projection::L2Projection() {}

L2Projection::L2Projection(Matrix &perm)
{
	projection = perm;
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

int L2Projection::NState() const
{
	return 1;
}

void L2Projection::Contribute(IntPointData &integrationpointdata, double weight, Matrix &EK, Matrix &EF) const
{

}

std::vector<double> L2Projection::PostProcess(const IntPointData & integrationpointdata, const PostProcVar var) const
{
	return std::vector<double>();
}