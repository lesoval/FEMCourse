#include <iostream>
#include "IntRule.h"
#include "IntRule1d.h"
#include "IntRuleQuad.h"
#include "IntRuleTriangle.h"
#include "IntRuleTetrahedron.h"
#include "Shape1d.h"
#include "ShapeQuad.h"
#include "ShapeTriangle.h"
#include "ShapeTetrahedron.h"
#include "Geom1d.h"

void main()
{
	IntRule1d a(7);
	IntRule b(a);
	std::cout << a.NPoints() << std::endl;
	std::cout << b.NPoints() << std::endl;

	system("pause");
}