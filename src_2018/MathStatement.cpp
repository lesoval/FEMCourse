/*
*  MathStatement.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "MathStatement.h"

double MathStatement::gBigNumber = DBL_MAX;

MathStatement::MathStatement() {}

MathStatement::MathStatement(const MathStatement &copy)
{
	this->operator=(copy);
}

MathStatement &MathStatement::operator=(const MathStatement &copy)
{
	matid = copy.matid;
	nstate = copy.nstate;

	return *this;
}

MathStatement::~MathStatement() {}

void MathStatement::Axes2XYZ(const Matrix & dudaxes, Matrix & dudx, const Matrix & axesv, bool colMajor) const
{
}
