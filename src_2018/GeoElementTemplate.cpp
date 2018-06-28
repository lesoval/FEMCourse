/*
*  GeomElementTemplate.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoElementTemplate.h"
#include "GeoMesh.h"
#include "Geom1d.h"
#include "GeomQuad.h"
#include "GeomTriangle.h"
#include "GeomTetrahedron.h"
#include "tpanic.h"

template<class TGeom>
GeoElementTemplate<TGeom>::GeoElementTemplate(const VecInt & nodeindices, int materialid, GeoMesh * gmesh, int index):GeoElement(materialid,gmesh,index)
{
	Geom.SetNodes(nodeindices);
}

template<class TGeom>
GeoElementTemplate<TGeom>::GeoElementTemplate(const GeoElementTemplate &copy)
{
	this->operator=(copy);
}

template<class TGeom>
GeoElementTemplate<TGeom> &GeoElementTemplate<TGeom>::operator=(const GeoElementTemplate &copy)
{
    Geom = copy.Geom;

	return *this;
}

template<class TGeom>
ElementType GeoElementTemplate<TGeom>::Type()
{
	return Geom.Type();
}

template<class TGeom>
void GeoElementTemplate<TGeom>::X(const VecDouble &xi, VecDouble &x)
{
	int nNodes = NNodes();
	int dim = x.size();
	Matrix NodeCo(dim, nNodes);

	for (int i = 0; i < nNodes; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			int NodeId = NodeIndex(i);
			NodeCo(j, i) = GMesh->Node(NodeId).Coord(j);
		}
	}

	Geom.X(xi, NodeCo, x);
}

template<class TGeom>
void GeoElementTemplate<TGeom>::GradX(const VecDouble &xi, VecDouble &x, Matrix &gradx)
{
	int nNodes = NNodes();
	int dim = x.size();
	Matrix NodeCo(dim, nNodes);

	for (int i = 0; i < nNodes; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			int NodeId = NodeIndex(i);
			NodeCo(j, i) = GMesh->Node(NodeId).Coord(j);
		}
	}

	Geom.GradX(xi, NodeCo, x, gradx);
}

template<class TGeom>
void GeoElementTemplate<TGeom>::Jacobian(const Matrix &gradx, Matrix &jac, Matrix &axes, double &detjac, Matrix &jacinv)
{	
	int nRows = gradx.Rows();
	int dim = gradx.Cols();

	switch (dim)
	{
	case 1:
	{
		jac.Resize(dim, dim);
		axes.Resize(dim, 3);
		jacinv.Resize(dim, dim);
		jac.Zero();

		/**  Definitions: v1 -> is the xi_direction of the Gradient */
		VecDouble v_1(3, 0.);

		for (int i = 0; i < nRows; i++) {
			v_1[i] = gradx.GetVal(i, 0);
		}

		double norm_v_1 = 0.;
		for (int i = 0; i < nRows; i++) {
			norm_v_1 += v_1[i] * v_1[i];
		}

		norm_v_1 = sqrt(norm_v_1);
		jac(0, 0) = norm_v_1;
		detjac = norm_v_1;
		jacinv(0, 0) = 1.0 / detjac;

		detjac = fabs(detjac);

		for (int i = 0; i < 3; i++) {
			axes(0, i) = v_1[i] / norm_v_1;
		}
	}
		break;

	case 2:
	{
		jac.Resize(dim, dim);
		axes.Resize(dim, 3);
		jacinv.Resize(dim, dim);
		jac.Zero();

		//Definitions: v1 -> is the xi_direction of the Gradient, v2 -> is the eta_direction of the Gradient
		VecDouble v_1(3, 0.), v_2(3, 0.);

		//Definitions: v_1_til and v_2_til -> asscoiated orthonormal vectors to v_1 and v_2
		VecDouble v_1_til(3, 0.), v_2_til(3, 0.);

		for (int i = 0; i < nRows; i++) {
			v_1[i] = gradx.GetVal(i, 0);
			v_2[i] = gradx.GetVal(i, 1);
		}

		double norm_v_1_til = 0.0;
		double norm_v_2_til = 0.0;
		double v_1_dot_v_2 = 0.0;

		for (int i = 0; i < 3; i++) {
			norm_v_1_til += v_1[i] * v_1[i];
			v_1_dot_v_2 += v_1[i] * v_2[i];
		}
		norm_v_1_til = sqrt(norm_v_1_til);

		for (int i = 0; i < 3; i++) {
			v_1_til[i] = v_1[i] / norm_v_1_til; // Normalizing
			v_2_til[i] = v_2[i] - v_1_dot_v_2 * v_1_til[i] / norm_v_1_til;
			norm_v_2_til += v_2_til[i] * v_2_til[i];
		}
		norm_v_2_til = sqrt(norm_v_2_til);


		jac(0, 0) = norm_v_1_til;
		jac(0, 1) = v_1_dot_v_2 / norm_v_1_til;
		jac(1, 1) = norm_v_2_til;

		detjac = jac(0, 0)*jac(1, 1) - jac(1, 0)*jac(0, 1);

		jacinv(0, 0) = +jac(1, 1) / detjac;
		jacinv(1, 1) = +jac(0, 0) / detjac;
		jacinv(0, 1) = -jac(0, 1) / detjac;
		jacinv(1, 0) = -jac(1, 0) / detjac;

		detjac = fabs(detjac);

		for (int i = 0; i < 3; i++) {
			v_2_til[i] /= norm_v_2_til; // Normalizing
			axes(0, i) = v_1_til[i];
			axes(1, i) = v_2_til[i];
		}
	}
		break;

	case 3:
	{
		jac.Resize(dim, dim);
		axes.Resize(dim, 3);
		jacinv.Resize(dim, dim);
		jac.Zero();

		for (int i = 0; i < nRows; i++) {
			jac(i, 0) = gradx.GetVal(i, 0);
			jac(i, 1) = gradx.GetVal(i, 1);
			jac(i, 2) = gradx.GetVal(i, 2);
		}

		detjac -= jac(0, 2)*jac(1, 1)*jac(2, 0);//- a02 a11 a20
		detjac += jac(0, 1)*jac(1, 2)*jac(2, 0);//+ a01 a12 a20
		detjac += jac(0, 2)*jac(1, 0)*jac(2, 1);//+ a02 a10 a21
		detjac -= jac(0, 0)*jac(1, 2)*jac(2, 1);//- a00 a12 a21
		detjac -= jac(0, 1)*jac(1, 0)*jac(2, 2);//- a01 a10 a22
		detjac += jac(0, 0)*jac(1, 1)*jac(2, 2);//+ a00 a11 a22

		jacinv(0, 0) = (-jac(1, 2)*jac(2, 1) + jac(1, 1)*jac(2, 2)) / detjac;//-a12 a21 + a11 a22
		jacinv(0, 1) = (jac(0, 2)*jac(2, 1) - jac(0, 1)*jac(2, 2)) / detjac;//a02 a21 - a01 a22
		jacinv(0, 2) = (-jac(0, 2)*jac(1, 1) + jac(0, 1)*jac(1, 2)) / detjac;//-a02 a11 + a01 a12
		jacinv(1, 0) = (jac(1, 2)*jac(2, 0) - jac(1, 0)*jac(2, 2)) / detjac;//a12 a20 - a10 a22
		jacinv(1, 1) = (-jac(0, 2)*jac(2, 0) + jac(0, 0)*jac(2, 2)) / detjac;//-a02 a20 + a00 a22
		jacinv(1, 2) = (jac(0, 2)*jac(1, 0) - jac(0, 0)*jac(1, 2)) / detjac;//a02 a10 - a00 a12
		jacinv(2, 0) = (-jac(1, 1)*jac(2, 0) + jac(1, 0)*jac(2, 1)) / detjac;//-a11 a20 + a10 a21
		jacinv(2, 1) = (jac(0, 1)*jac(2, 0) - jac(0, 0)*jac(2, 1)) / detjac;//a01 a20 - a00 a21
		jacinv(2, 2) = (-jac(0, 1)*jac(1, 0) + jac(0, 0)*jac(1, 1)) / detjac;//-a01 a10 + a00 a11

																			 //            detjac = fabs(detjac);

		axes.Zero();
		axes(0, 0) = 1.0;
		axes(1, 1) = 1.0;
		axes(2, 2) = 1.0;
	}
		break;

	default:
		std::cout << "GeoElement::Jacobian --> Inconsistent matrix dimension." << std::endl;
		DebugStop();
		break;
	}
}

template<class TGeom>
int GeoElementTemplate<TGeom>::SideIsUndefined(int side)
{
	return 0;
}

template<class TGeom>
int GeoElementTemplate<TGeom>::WhichSide(VecInt & SideNodeIds)
{
	int size = SideNodeIds.size();

	switch (size)
	{
	case 2:

		for (int i = NCornerNodes(); i < NSides(); i++)
		{
			if (NSideNodes(i) == 2)
			{
				if ((SideNodeIds[0] == SideNodeIndex(i, 0) && SideNodeIds[1] == SideNodeIndex(i, 1)) ||
					(SideNodeIds[1] == SideNodeIndex(i, 0) && SideNodeIds[0] == SideNodeIndex(i, 1)))
				{
					return i;
					break;
				}
			}
			
		}
		break;

	case 3:

		for (int i = NCornerNodes(); NSides(); i++)
		{
			if (NSideNodes(i) == 3)
			{
				if ((SideNodeIds[0] == SideNodeIndex(i, 0) && SideNodeIds[1] == SideNodeIndex(i, 1) && SideNodeIds[2] == SideNodeIndex(i, 2)) ||
					(SideNodeIds[1] == SideNodeIndex(i, 0) && SideNodeIds[2] == SideNodeIndex(i, 1) && SideNodeIds[0] == SideNodeIndex(i, 2)) ||
					(SideNodeIds[2] == SideNodeIndex(i, 0) && SideNodeIds[0] == SideNodeIndex(i, 1) && SideNodeIds[1] == SideNodeIndex(i, 2)))
				{
					return i;
					break;
				}
			}
		}
		break;

	case 4:

		for (int i = NCornerNodes(); i < NSides(); i++)
		{
			if (NSideNodes(i) == 4)
			{
				if ((SideNodeIds[0] == SideNodeIndex(i, 0) && SideNodeIds[1] == SideNodeIndex(i, 1) && SideNodeIds[2] == SideNodeIndex(i, 2) && SideNodeIds[3] == SideNodeIndex(i, 3)) ||
					(SideNodeIds[1] == SideNodeIndex(i, 0) && SideNodeIds[2] == SideNodeIndex(i, 1) && SideNodeIds[3] == SideNodeIndex(i, 2) && SideNodeIds[0] == SideNodeIndex(i, 3)) ||
					(SideNodeIds[2] == SideNodeIndex(i, 0) && SideNodeIds[3] == SideNodeIndex(i, 1) && SideNodeIds[0] == SideNodeIndex(i, 2) && SideNodeIds[1] == SideNodeIndex(i, 3)) ||
					(SideNodeIds[3] == SideNodeIndex(i, 0) && SideNodeIds[0] == SideNodeIndex(i, 1) && SideNodeIds[1] == SideNodeIndex(i, 2) && SideNodeIds[2] == SideNodeIndex(i, 3)))
				{
					return i;
					break;
				}
			}
		}
		break;

	default:

		std::cout << "GeoElement::WhichSide : Inconsistent geometrie detected" << std::endl;
		DebugStop();

		break;
	}
}

template<class TGeom>
void GeoElementTemplate<TGeom>::Print(std::ostream &out)
{
	out << "ELEMENT: " << Index << "\tTYPE: " << Type() << "\t\tMatID: " << MaterialId << "\tNODES(";
	for (int i = 0; i < NNodes(); i++)
	{
		if (i != 0)
		{
			out << ", ";
		}
		out << NodeIndex(i);
	}
	out << ")\n" << std::endl;

	for (int i = 0; i < NSides(); i++)
	{
		out << "NEIGHBOURS (SIDE " << i << "): ";
		GeoElementSide neighbour = Neighbour(i);
		GeoElementSide thiside(this, i);
		if (neighbour==thiside)
		{
			out << "NO NEIGHBOUR" << std::endl;
		}
		else
		{
			while (neighbour != thiside)
			{
				out << "(ELEMENT " << neighbour.Element()->GetIndex() << " / SIDE " << neighbour.Side() << "), ";
				neighbour = neighbour.Neighbour();
			}
			out << '\b' << '\b' << " " << std::endl;
		}
	}
	out << "\n" << std::endl;
}

template class GeoElementTemplate<Geom1d>;
template class GeoElementTemplate<GeomQuad>;
template class GeoElementTemplate<GeomTriangle>;
template class GeoElementTemplate<GeomTetrahedron>;