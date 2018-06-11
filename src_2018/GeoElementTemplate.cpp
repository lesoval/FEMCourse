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
	int dim = gradx.Rows();
	int nShapes = gradx.Cols();

	jac.Resize(dim, dim);
	jacinv.Resize(dim, dim);
	axes.Zero();

	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			jac(i, j) = gradx.GetVal(j, i);
		}
	}

	switch (dim)
	{
	case 1:
		detjac = jac(0, 0);
		jacinv(0, 0) = 1 / detjac;
		axes(0, 0) = 1;

		break;

	case 2:
		detjac = jac(0, 0)*jac(1, 1) - jac(0, 1)*jac(1, 0);

		jacinv(0, 0) = jac(1, 1) / detjac;
		jacinv(1, 1) = jac(0, 0) / detjac;
		jacinv(0, 1) = -jac(0, 1) / detjac;
		jacinv(1, 0) = -jac(1, 0) / detjac;
		
		axes(0, 0) = 1;
		axes(1, 1) = 1;

		break;

	case 3:
		double pos, neg;
		pos = jac(0, 0)*jac(1, 1)*jac(2, 2) + jac(0, 1)*jac(1, 2)*jac(2, 0) + jac(0, 2)*jac(1, 0)*jac(2, 1);
		neg = jac(0, 2)*jac(1, 1)*jac(2, 0) + jac(0, 1)*jac(1, 0)*jac(2, 2) + jac(0, 0)*jac(1, 2)*jac(2, 1);
		detjac = pos - neg;

		jacinv(0, 0) = (-jac(1, 2)*jac(2, 1) + jac(1, 1)*jac(2, 2)) / detjac;
		jacinv(0, 1) = (jac(0, 2)*jac(2, 1) - jac(0, 1)*jac(2, 2)) / detjac;
		jacinv(0, 2) = (-jac(0, 2)*jac(1, 1) + jac(0, 1)*jac(1, 2)) / detjac;
		jacinv(1, 0) = (jac(1, 2)*jac(2, 0) - jac(1, 0)*jac(2, 2)) / detjac;
		jacinv(1, 1) = (-jac(0, 2)*jac(2, 0) + jac(0, 0)*jac(2, 2)) / detjac;
		jacinv(1, 2) = (jac(0, 2)*jac(1, 0) - jac(0, 0)*jac(1, 2)) / detjac;
		jacinv(2, 0) = (-jac(1, 1)*jac(2, 0) + jac(1, 0)*jac(2, 1)) / detjac;
		jacinv(2, 1) = (jac(0, 1)*jac(2, 0) - jac(0, 0)*jac(2, 1)) / detjac;
		jacinv(2, 2) = (-jac(0, 1)*jac(1, 0) + jac(0, 0)*jac(1, 1)) / detjac;

		axes(0, 0) = 1.0;
		axes(1, 1) = 1.0;
		axes(2, 2) = 1.0;

		break;

	default:
		std::cout << "GeoElement::Jacobian --> Inconsistent matrix dimension." << std::endl;
		DebugStop();
		break;
	}
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