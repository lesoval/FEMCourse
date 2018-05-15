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
void GeoElementTemplate<TGeom>::Print(std::ostream &out)
{
    
}

template class GeoElementTemplate<Geom1d>;
template class GeoElementTemplate<GeomQuad>;
template class GeoElementTemplate<GeomTriangle>;
template class GeoElementTemplate<GeomTetrahedron>;