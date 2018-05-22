/*
*  GeomElementTemplate.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoElementTemplate.h"
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
    
}

template<class TGeom>
void GeoElementTemplate<TGeom>::GradX(const VecDouble &xi, VecDouble &x, Matrix &gradx)
{
    
}

template<class TGeom>
void GeoElementTemplate<TGeom>::Jacobian(const Matrix &gradx, Matrix &jac, Matrix &axes, double &detjac, Matrix &jacinv)
{

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