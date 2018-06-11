#include <iostream>
#include "Shape1d.h"
#include "ShapeQuad.h"
#include "ShapeTriangle.h"
#include "ShapeTetrahedron.h"
#include "Geom1d.h"
#include "GeomQuad.h"
#include "GeomTriangle.h"
#include "GeomTetrahedron.h"
#include "GeoElement.h"
#include "GeoElementSide.h"
#include "GeoElementTemplate.h"
#include "GeoMesh.h"
#include "CompElement.h"
#include "CompElementTemplate.h"
#include "CompMesh.h"
#include "Poisson.h"
#include "ReadGmsh.h"
#include "MathStatement.h"
#include "Assemble.h"

void F(const VecDouble &x, VecDouble &f) { f.resize(3); f[0] = 1000 * x[0]; f[1] = 0; f[2] = 0; }

void main()
{
	VecDouble a(2); a[0] = 0; a[1] = 0;
	VecDouble b(2); b[0] = 4; b[1] = 0;
	VecDouble c(2); c[0] = 4; c[1] = 2;
	VecDouble d(2); d[0] = 0; d[1] = 2;
	VecDouble e(2); e[0] = 8; e[1] = 0;
	VecDouble f(2); f[0] = 8; f[1] = 2;

	GeoMesh gmesh; gmesh.SetNumElements(2); gmesh.SetNumNodes(6);
	gmesh.Node(0).SetCo(a);
	gmesh.Node(1).SetCo(b);
	gmesh.Node(2).SetCo(c);
	gmesh.Node(3).SetCo(d);
	gmesh.Node(4).SetCo(e);
	gmesh.Node(5).SetCo(f);

	int matid = 0;
	VecInt Top1(4); Top1[0] = 0; Top1[1] = 1; Top1[2] = 2; Top1[3] = 3;
	GeoElement *gel1 = new GeoElementTemplate<GeomQuad>(Top1, matid, &gmesh, 0);
	VecInt Top2(4); Top2[0] = 1; Top2[1] = 4; Top2[2] = 5; Top2[3] = 2;
	GeoElement *gel2 = new GeoElementTemplate<GeomQuad>(Top2, matid, &gmesh, 1);
	gmesh.SetElement(0, gel1); gmesh.SetElement(1, gel2);
	gmesh.BuildConnectivity();

	Matrix perm(2, 2, 1); perm(1, 0) = 0; perm(0, 1) = 0;
	Poisson *q = new Poisson(matid, perm); q->SetForceFunction(F);
	CompMesh cmesh(&gmesh); cmesh.SetDefaultOrder(1); cmesh.SetNumberMath(1); cmesh.SetMathStatement(matid, q);
	cmesh.AutoBuild();

	Assemble k(&cmesh);
	Matrix globmat, rhs;
	k.Compute(globmat, rhs);
	
	//globmat.Print(std::cout);

	system("pause");
}


//BuildConnectivity Test
/* void main()
{
	VecDouble a(2); a[0] = 0; a[1] = 0;
	VecDouble b(2); b[0] = 5; b[1] = 0;
	VecDouble c(2); c[0] = 5; c[1] = 5;
	VecDouble d(2); d[0] = 0; d[1] = 5;
	VecDouble e(2); e[0] = 10; e[1] = 0;
	VecDouble f(2); f[0] = 10; f[1] = 5;
	VecDouble g(2); g[0] = 5; g[1] = 10;

	GeoMesh gmesh; gmesh.SetNumElements(4); gmesh.SetNumNodes(7);
	gmesh.Node(0).SetCo(a);
	gmesh.Node(1).SetCo(b);
	gmesh.Node(2).SetCo(c);
	gmesh.Node(3).SetCo(d);
	gmesh.Node(4).SetCo(e);
	gmesh.Node(5).SetCo(f);
	gmesh.Node(6).SetCo(g);

	VecInt Top1(4); Top1[0] = 0; Top1[1] = 1; Top1[2] = 2; Top1[3] = 3;
	GeoElement *gel1 = new GeoElementTemplate<GeomQuad>(Top1, 0, &gmesh, 0);

	VecInt Top2(4); Top2[0] = 1; Top2[1] = 4; Top2[2] = 5; Top2[3] = 2;
	GeoElement *gel2 = new GeoElementTemplate<GeomQuad>(Top2, 0, &gmesh, 1);

	VecInt Top3(2); Top3[0] = 1; Top3[1] = 2;
	GeoElement *gel3 = new GeoElementTemplate<Geom1d>(Top3, 0, &gmesh, 2);

	VecInt Top4(2); Top4[0] = 2; Top4[1] = 6;
	GeoElement *gel4 = new GeoElementTemplate<Geom1d>(Top4, 0, &gmesh, 3);

	//VecInt Top5(4); Top5[0] = 0; Top5[1] = 1; Top5[2] = 2; Top5[3] = 3;
	//GeoElement *gel5 = new GeoElementTemplate<GeomQuad>(Top5, 0, &gmesh, 4);

	gmesh.SetElement(0, gel1);
	gmesh.SetElement(1, gel2);
	gmesh.SetElement(2, gel3);
	gmesh.SetElement(3, gel4);
	//gmesh.SetElement(4, gel5);
	gmesh.BuildConnectivity();
	gmesh.Print(std::cout);

	//int el= gel1->Neighbour(8).Element()->GetIndex();
	//int side = gel1->Neighbour(8).Side();

	//std::cout << el << std::endl << side << std::endl;

	//std::cout << neighbours.size() << std::endl;
	//std::cout << neighbours[0].Element()->GetIndex() << std::endl;

	system("pause");
}*/