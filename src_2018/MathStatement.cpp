/*
*  MathStatement.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "MathStatement.h"

double MathStatement::gBigNumber = 1e300;

MathStatement::MathStatement() {}

MathStatement::MathStatement(const MathStatement &copy)
{
	this->operator=(copy);
}

MathStatement &MathStatement::operator=(const MathStatement &copy)
{
	matid = copy.matid;

	return *this;
}

MathStatement::~MathStatement() {}

void MathStatement::Axes2XYZ(const Matrix & dudaxes, Matrix & dudx, const Matrix & axesv, bool colMajor) const
{
	int dim = Dimension();
	int nShapes = dudaxes.Cols();
	dudx.Resize(dim, nShapes);
	
	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			for (int k = 0; k < dudaxes.Rows(); k++)
			{
				dudx(j, i) += dudaxes.GetVal(k, i)*axesv.GetVal(k, j);
			}
		}
	}
}

void MathStatement::Print(std::ostream & out)
{
}
