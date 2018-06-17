/*
*  CompElement.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "CompElement.h"
#include "GeoElement.h"
#include "MathStatement.h"

CompElement::CompElement() {}

CompElement::CompElement(int64_t ind, CompMesh *cmesh, GeoElement *geo)
{
	SetIndex(ind);
	SetGeoElement(geo);
	SetCompMesh(cmesh);
	geo->SetReference(this);
}

CompElement::CompElement(const CompElement &copy)
{
	this->operator=(copy);
}

CompElement &CompElement::operator=(const CompElement &copy)
{
	index = copy.index;
	geoel = copy.geoel;
	compmesh = copy.compmesh;
	intrule = copy.intrule;
	mat = copy.mat;

	return *this;
}

CompElement::~CompElement() {}

CompElement *CompElement::Clone() const
{
	return 0;
}

MathStatement *CompElement::GetStatement() const
{
	return mat;
}

void CompElement::SetStatement(MathStatement *statelement)
{
	mat = statelement;
}

IntRule *CompElement::GetIntRule() const
{
	return intrule;
}

void CompElement::SetIntRule(IntRule *intrule)
{
	this->intrule = intrule;
}

void CompElement::SetIndex(int64_t ind)
{
	index = ind;
}

GeoElement *CompElement::GetGeoElement() const
{
	return geoel;
}

void CompElement::SetGeoElement(GeoElement *element)
{
	geoel = element;
}

CompMesh *CompElement::GetCompMesh() const
{
	return compmesh;
}

void CompElement::SetCompMesh(CompMesh *mesh)
{
	compmesh = mesh;
}

void CompElement::InitializeIntPointData(IntPointData &data) const
{
	int dim = Dimension();
	int nShapes = NShapeFunctions();
	int nState = GetStatement()->NState();
	
	data.weight = 0;
	data.detjac = 0;

	data.axes.Resize(dim, dim);
	data.x.resize(3);
	data.ksi.resize(dim);

	data.phi.resize(nShapes);
	data.dphidksi.Resize(dim, nShapes);

	data.gradx.Resize(dim, nShapes);
	data.dphidx.Resize(dim, nShapes);

	data.solution.resize(nState);
	data.dsoldksi.Resize(dim, nState);
	data.dsoldx.Resize(dim, nState);

}

void CompElement::ComputeRequiredData(IntPointData &data, VecDouble &intpoint) const
{
	Matrix gradx, jac, jacinv;

	geoel->X(intpoint, data.x);
	geoel->GradX(intpoint, data.x, gradx);
	geoel->Jacobian(gradx, jac, data.axes, data.detjac, jacinv);

	ShapeFunctions(intpoint, data.phi, data.dphidksi);
	Convert2Axes(data.dphidksi, jacinv, data.dphidx);
}

void CompElement::Convert2Axes(const Matrix & dphi, const Matrix & jacinv, Matrix & dphidx) const
{
	int nShapes = NShapeFunctions();
	int dim = Dimension();

	for (int i = 0; i < nShapes; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			for (int k = 0; k < dim; k++)
			{
				dphidx(j, i) += jacinv.GetVal(k, j)*dphi.GetVal(k, i);
			}
		}
	}
}

void CompElement::CalcStiff(Matrix &ek, Matrix &ef) const
{
	IntPointData data;
	InitializeIntPointData(data);
	
	int dim = Dimension();
	int nShapes = NShapeFunctions();
	int nStates = GetStatement()->NState();
	int nIntpoints = intrule->NPoints();

	ek.Resize(nShapes*nStates, nShapes*nStates);
	ef.Resize(nShapes*nStates, 1);

	for (int i = 0; i < nIntpoints; i++)
	{
		intrule->Point(i, data.ksi, data.weight);
		ComputeRequiredData(data, data.ksi);

		GetStatement()->Contribute(data, data.weight, ek, ef);
	}
}

void CompElement::EvaluateError(std::function<void(const VecDouble&loc, VecDouble&val, Matrix&deriv)> fp, VecDouble & errors) const
{
}

void CompElement::Solution(VecDouble & intpoint, int var, VecDouble & sol, TMatrix & dsol) const
{
	IntPointData data;
	InitializeIntPointData(data);
	ComputeRequiredData(data, intpoint);
	GetMultiplyingCoeficients(data.coefs);

	data.ComputeSolution();

	sol = data.solution;
	dsol = data.dsoldx;
}