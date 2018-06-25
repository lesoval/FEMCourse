#include <iostream>
#include <string>
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
#include "VTKGeoMesh.h"
#include "ReadGmsh.h"
#include "MathStatement.h"
#include "Assemble.h"
#include "Analysis.h"
#include "PlaneStressShell.h"
#include "PlaneStrainShell.h"
#include "OnlyForce.h"
#include "Restrain.h"

void TestQuad(const int order);
void TestTriangle(const int order);
void PlaneStressTest(const std::string Malha, const int order);
void VasselTest(const std::string Malha, const int order);

void main()
{
	//TestQuad(2);
	//TestTriangle(2);
	//PlaneStressTest("BasicMesh", 2);
	VasselTest("Vassel", 1);

	system("pause");
}

//Pressure vessel - Plane Strain
void VasselTest(const std::string Malha, const int order)
{
	GeoMesh gmesh;
	
	ReadGmsh *teste = new ReadGmsh();
	teste->Read(gmesh, Malha + ".msh");
	gmesh.BuildConnectivity();
	//gmesh.Print(std::cout);
	VTKGeoMesh::PrintGMeshVTK(&gmesh, "G" + Malha + ".vtk");

	PlaneStrainShell *Elasticity = new PlaneStrainShell(1, 2.1e5, 0.3, 1);
	OnlyForce *Force1 = new OnlyForce(2);
	auto carga1 = [](const VecDouble &x, VecDouble &f)
	{
		double hip = sqrt(x[0] * x[0] + x[1] * x[1]);

		f[0] = 100 * x[0] / hip;
		f[1] = 100 * x[1] / hip;
	};
	Force1->SetForceFunction(carga1);

	OnlyForce *Force2 = new OnlyForce(3);
	auto carga2 = [](const VecDouble &x, VecDouble &f)
	{
		double hip = sqrt(x[0] * x[0] + x[1] * x[1]);

		f[0] = -75 * x[0] / hip;
		f[1] = -75 * x[1] / hip;
	};
	Force2->SetForceFunction(carga2);
	//Restrain *Rest = new Restrain(3);

	CompMesh cmesh(&gmesh); cmesh.SetDefaultOrder(order); cmesh.SetNumberMath(3);
	cmesh.SetMathStatement(1, Elasticity);
	cmesh.SetMathStatement(2, Force1);
	cmesh.SetMathStatement(3, Force2);
	cmesh.AutoBuild();

	Analysis an(&cmesh);
	an.RunSimulation();

	VTKGeoMesh::PrintCMeshVTK(&cmesh, 2, "C" + Malha + ".vtk");
}

//PlaneStressShell Test
void PlaneStressTest(const std::string Malha, const int order)
{
	GeoMesh gmesh;
	
	ReadGmsh *teste = new ReadGmsh();
	teste->Read(gmesh, Malha + ".msh");
	gmesh.BuildConnectivity();
	//gmesh.Print(std::cout);
	VTKGeoMesh::PrintGMeshVTK(&gmesh, "G" + Malha + ".vtk");

	PlaneStressShell *Elasticity = new PlaneStressShell(1, 2.1e8, 0.3, 0.025);
	Restrain *Rest = new Restrain(2);
	OnlyForce *Force = new OnlyForce(3);
	auto carga = [](const VecDouble &x, VecDouble &f)
	{
		f[0] = 0;
		f[1] = -75;
	};
	Force->SetForceFunction(carga);

	CompMesh cmesh(&gmesh); cmesh.SetDefaultOrder(order); cmesh.SetNumberMath(3);
	cmesh.SetMathStatement(1, Elasticity);
	cmesh.SetMathStatement(2, Rest); 
	cmesh.SetMathStatement(3, Force);
	cmesh.AutoBuild();

	Analysis an(&cmesh);
	an.RunSimulation();

	VTKGeoMesh::PrintCMeshVTK(&cmesh, 2, "C" + Malha + ".vtk");
}

//Plane Stress Test Triangle - Mixed boundary
void TestTriangle(const int order)
{
	VecDouble a(3);		a[0] = 0;		a[1] = 0;		a[2] = 0;
	VecDouble b(3);		b[0] = 0.5;		b[1] = 0;		b[2] = 0;
	VecDouble c(3);		c[0] = 0.5;		c[1] = 0.25;	c[2] = 0;
	VecDouble d(3);		d[0] = 0;		d[1] = 0.25;	d[2] = 0;

	GeoMesh gmesh; gmesh.SetNumElements(4); gmesh.SetNumNodes(4);
	gmesh.Node(0).SetCo(a);
	gmesh.Node(1).SetCo(b);
	gmesh.Node(2).SetCo(c);
	gmesh.Node(3).SetCo(d);

	VecInt Top1(3); Top1[0] = 0; Top1[1] = 2; Top1[2] = 3;
	GeoElement *gel1 = new GeoElementTemplate<GeomTriangle>(Top1, 1, &gmesh, 0);
	VecInt Top2(3); Top2[0] = 0; Top2[1] = 1; Top2[2] = 2;
	GeoElement *gel2 = new GeoElementTemplate<GeomTriangle>(Top2, 1, &gmesh, 1);
	VecInt Top3(2); Top3[0] = 1; Top3[1] = 2;
	GeoElement *gel3 = new GeoElementTemplate<Geom1d>(Top3, 2, &gmesh, 2);
	VecInt Top4(2); Top4[0] = 0; Top4[1] = 3;
	GeoElement *gel4 = new GeoElementTemplate<Geom1d>(Top4, 3, &gmesh, 3);
	gmesh.SetElement(0, gel1); gmesh.SetElement(1, gel2); gmesh.SetElement(2, gel3); gmesh.SetElement(3, gel4);

	gmesh.BuildConnectivity();

	//gmesh.Print(std::cout);
	VTKGeoMesh::PrintGMeshVTK(&gmesh, "GTestTriangle.vtk");

	PlaneStressShell *Elasticity = new PlaneStressShell(1, 2.1e8, 0.3, 0.025);
	OnlyForce *Force = new OnlyForce(2);
	auto carga = [](const VecDouble &x, VecDouble &f)
	{
		f[0] = 75;
		f[1] = 0;
	};
	Force->SetForceFunction(carga);
	Restrain *Rest = new Restrain(3);

	CompMesh cmesh(&gmesh); cmesh.SetDefaultOrder(order); cmesh.SetNumberMath(3);
	cmesh.SetMathStatement(1, Elasticity);
	cmesh.SetMathStatement(2, Force);
	cmesh.SetMathStatement(3, Rest);
	cmesh.AutoBuild();

	Analysis an(&cmesh);
	an.RunSimulation();

	VTKGeoMesh::PrintCMeshVTK(&cmesh, 2, "CTestTriangle.vtk");
}

//Plane Stress Test Quad - Mixed boundary
void TestQuad(const int order)
{
	VecDouble a(3);		a[0] = 0;		a[1] = 0;		a[2] = 0;
	VecDouble b(3);		b[0] = 0.25;	b[1] = 0;		b[2] = 0;
	VecDouble c(3);		c[0] = 0.5;		c[1] = 0;		c[2] = 0;
	VecDouble d(3);		d[0] = 0;		d[1] = 0.25;	d[2] = 0;
	VecDouble e(3);		e[0] = 0.25;	e[1] = 0.25;	e[2] = 0;
	VecDouble f(3);		f[0] = 0.5;		f[1] = 0.25;	f[2] = 0;

	GeoMesh gmesh; gmesh.SetNumElements(4); gmesh.SetNumNodes(6);
	gmesh.Node(0).SetCo(a);
	gmesh.Node(1).SetCo(b);
	gmesh.Node(2).SetCo(c);
	gmesh.Node(3).SetCo(d);
	gmesh.Node(4).SetCo(e);
	gmesh.Node(5).SetCo(f);

	VecInt Top1(4); Top1[0] = 0; Top1[1] = 1; Top1[2] = 4; Top1[3] = 3;
	GeoElement *gel1 = new GeoElementTemplate<GeomQuad>(Top1, 1, &gmesh, 0);
	VecInt Top2(4); Top2[0] = 1; Top2[1] = 2; Top2[2] = 5; Top2[3] = 4;
	GeoElement *gel2 = new GeoElementTemplate<GeomQuad>(Top2, 1, &gmesh, 1);
	VecInt Top3(2); Top3[0] = 2; Top3[1] = 5;
	GeoElement *gel3 = new GeoElementTemplate<Geom1d>(Top3, 2, &gmesh, 2);
	VecInt Top4(2); Top4[0] = 0; Top4[1] = 3;
	GeoElement *gel4 = new GeoElementTemplate<Geom1d>(Top4, 3, &gmesh, 3);
	gmesh.SetElement(0, gel1); gmesh.SetElement(1, gel2); gmesh.SetElement(2, gel3); gmesh.SetElement(3, gel4);

	gmesh.BuildConnectivity();

	//gmesh.Print(std::cout);
	VTKGeoMesh::PrintGMeshVTK(&gmesh, "GTestQuad.vtk");

	PlaneStressShell *Elasticity = new PlaneStressShell(1, 2.1e8, 0.3, 0.025);
	OnlyForce *Force = new OnlyForce(2);
	auto carga = [](const VecDouble &x, VecDouble &f)
	{
		f[0] = 75;
		f[1] = 0;
	};
	Force->SetForceFunction(carga);
	Restrain *Rest = new Restrain(3);

	CompMesh cmesh(&gmesh); cmesh.SetDefaultOrder(order); cmesh.SetNumberMath(3);
	cmesh.SetMathStatement(1, Elasticity);
	cmesh.SetMathStatement(2, Force);
	cmesh.SetMathStatement(3, Rest);
	cmesh.AutoBuild();

	Analysis an(&cmesh);
	an.RunSimulation();

	VTKGeoMesh::PrintCMeshVTK(&cmesh, 2, "CTestQuad.vtk");
}