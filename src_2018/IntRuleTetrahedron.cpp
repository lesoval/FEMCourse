#include <iomanip>
#include <math.h>
#include "IntRuleTetrahedron.h"
#include "tpanic.h"

IntRuleTetrahedron::IntRuleTetrahedron() :IntRule() {}

IntRuleTetrahedron::IntRuleTetrahedron(int order) : IntRule(order) {}

int IntRuleTetrahedron::NPoints() const
{
	int npoints;

	if (fOrder<0 || fOrder > 5)
	{
		DebugStop();
	}

	if (fOrder == 0 || fOrder == 1)
	{
		npoints = 1;
	}

	if (fOrder == 2)
	{
		npoints = 4;
	}

	if (fOrder == 3)
	{
		npoints = 5;
	}

	if (fOrder == 4)
	{
		npoints = 11;
	}

	if (fOrder == 5)
	{
		npoints = 15;
	}

	return npoints;
}

void IntRuleTetrahedron::Print(std::ostream &out) const
{
	out << "ORDER	" << fOrder << "	NPoints	" << NPoints() << "\n" << std::endl;

	for (int i = 0; i < NPoints(); i++)
	{
		VecDouble co(NPoints());
		double weight;
		IntRuleTetrahedron T(fOrder);
		T.Point(i, co, weight);
		std::cout << std::setprecision(12) << std::fixed;
		out << "POINT	" << i << "	POS {" << co[0] << ", " << co[1] << ", " << co[2]
			<< "}	WEIGHT " << weight << std::endl;
	}
}

void IntRuleTetrahedron::Point(int p, VecDouble &co, double &weight)
{
	if (p<0 || p >= NPoints())
	{
		DebugStop();
	}

	if (fOrder == 0 || fOrder == 1) {

		fPoints.Resize(1, 3);
		fWeights.resize(1);

		fPoints.PutVal(0, 0, 0.2500000000000000);  fPoints.PutVal(0, 1, 0.2500000000000000); fPoints.PutVal(0, 2, 0.2500000000000000); fWeights[0] = 0.1666666666666666;
	}

	if (fOrder == 2) {

		fPoints.Resize(4, 3);
		fWeights.resize(4);

		fPoints.PutVal(0, 0, 0.1381966011250110);  fPoints.PutVal(0, 1, 0.1381966011250110); fPoints.PutVal(0, 2, 0.1381966011250110); fWeights[0] = 0.0416666666666666;
		fPoints.PutVal(1, 0, 0.1381966011250110);  fPoints.PutVal(1, 1, 0.1381966011250110); fPoints.PutVal(1, 2, 0.5854101966249680); fWeights[1] = 0.0416666666666666;
		fPoints.PutVal(2, 0, 0.1381966011250110);  fPoints.PutVal(2, 1, 0.5854101966249680); fPoints.PutVal(2, 2, 0.1381966011250110); fWeights[2] = 0.0416666666666666;
		fPoints.PutVal(3, 0, 0.5854101966249680);  fPoints.PutVal(3, 1, 0.1381966011250110); fPoints.PutVal(3, 2, 0.1381966011250110); fWeights[3] = 0.0416666666666666;
	}

	if (fOrder == 3) {

		fPoints.Resize(5, 3);
		fWeights.resize(5);

		fPoints.PutVal(0, 0, 0.2500000000000000);  fPoints.PutVal(0, 1, 0.2500000000000000); fPoints.PutVal(0, 2, 0.2500000000000000); fWeights[0] = -0.13333333333333333;
		fPoints.PutVal(1, 0, 0.1666666666666666);  fPoints.PutVal(1, 1, 0.1666666666666666); fPoints.PutVal(1, 2, 0.1666666666666666); fWeights[1] = 0.0750000000000000;
		fPoints.PutVal(2, 0, 0.1666666666666666);  fPoints.PutVal(2, 1, 0.1666666666666666); fPoints.PutVal(2, 2, 0.500000000000000); fWeights[2] = 0.0750000000000000;
		fPoints.PutVal(3, 0, 0.1666666666666666);  fPoints.PutVal(3, 1, 0.500000000000000); fPoints.PutVal(3, 2, 0.1666666666666666); fWeights[3] = 0.0750000000000000;
		fPoints.PutVal(4, 0, 0.500000000000000);  fPoints.PutVal(4, 1, 0.1666666666666666); fPoints.PutVal(4, 2, 0.1666666666666666); fWeights[4] = 0.0750000000000000;
	}

	if (fOrder == 4) {

		fPoints.Resize(11, 3);
		fWeights.resize(11);

		fPoints.PutVal(0, 0, 0.250000000000000);  fPoints.PutVal(0, 1, 0.250000000000000); fPoints.PutVal(0, 2, 0.250000000000000); fWeights[0] = -0.013155555556;
		fPoints.PutVal(1, 0, 0.071428571428571);  fPoints.PutVal(1, 1, 0.071428571428571); fPoints.PutVal(1, 2, 0.071428571428571); fWeights[1] = 0.007622222222;
		fPoints.PutVal(2, 0, 0.785714285714286);  fPoints.PutVal(2, 1, 0.071428571428571); fPoints.PutVal(2, 2, 0.071428571428571); fWeights[2] = 0.007622222222;
		fPoints.PutVal(3, 0, 0.071428571428571);  fPoints.PutVal(3, 1, 0.785714285714286); fPoints.PutVal(3, 2, 0.071428571428571); fWeights[3] = 0.007622222222;
		fPoints.PutVal(4, 0, 0.071428571428571);  fPoints.PutVal(4, 1, 0.071428571428571); fPoints.PutVal(4, 2, 0.785714285714286); fWeights[4] = 0.007622222222;
		fPoints.PutVal(5, 0, 0.399403576166799);  fPoints.PutVal(5, 1, 0.100596423833201); fPoints.PutVal(5, 2, 0.100596423833201); fWeights[5] = 0.024888888889;
		fPoints.PutVal(6, 0, 0.100596423833201);  fPoints.PutVal(6, 1, 0.399403576166799); fPoints.PutVal(6, 2, 0.100596423833201); fWeights[6] = 0.024888888889;
		fPoints.PutVal(7, 0, 0.100596423833201);  fPoints.PutVal(7, 1, 0.100596423833201); fPoints.PutVal(7, 2, 0.399403576166799); fWeights[7] = 0.024888888889;
		fPoints.PutVal(8, 0, 0.399403576166799);  fPoints.PutVal(8, 1, 0.399403576166799); fPoints.PutVal(8, 2, 0.100596423833201); fWeights[8] = 0.024888888889;
		fPoints.PutVal(9, 0, 0.399403576166799);  fPoints.PutVal(9, 1, 0.100596423833201); fPoints.PutVal(9, 2, 0.1666666666666666); fWeights[9] = 0.024888888889;
		fPoints.PutVal(10, 0, 0.100596423833201);  fPoints.PutVal(10, 1, 0.399403576166799); fPoints.PutVal(10, 2, 0.1666666666666666); fWeights[10] = 0.024888888889;
	}

	if (fOrder == 5) {

		fPoints.Resize(15, 3);
		fWeights.resize(15);

		fPoints.PutVal(0, 0, 0.250000000000000);  fPoints.PutVal(0, 1, 0.250000000000000); fPoints.PutVal(0, 2, 0.250000000000000); fWeights[0] = 0.030283678097089;
		fPoints.PutVal(1, 0, 0.333333333333333);  fPoints.PutVal(1, 1, 0.333333333333333); fPoints.PutVal(1, 2, 0.333333333333333); fWeights[1] = 0.006026785714286;
		fPoints.PutVal(2, 0, 0.000000000000000);  fPoints.PutVal(2, 1, 0.333333333333333); fPoints.PutVal(2, 2, 0.333333333333333); fWeights[2] = 0.006026785714286;
		fPoints.PutVal(3, 0, 0.000000000000000);  fPoints.PutVal(3, 1, 0.000000000000000); fPoints.PutVal(3, 2, 0.333333333333333); fWeights[3] = 0.006026785714286;
		fPoints.PutVal(4, 0, 0.333333333333333);  fPoints.PutVal(4, 1, 0.333333333333333); fPoints.PutVal(4, 2, 0.000000000000000); fWeights[4] = 0.006026785714286;
		fPoints.PutVal(5, 0, 0.090909090909091);  fPoints.PutVal(5, 1, 0.090909090909091); fPoints.PutVal(5, 2, 0.090909090909091); fWeights[5] = 0.011645249086029;
		fPoints.PutVal(6, 0, 0.727272727272727);  fPoints.PutVal(6, 1, 0.090909090909091); fPoints.PutVal(6, 2, 0.090909090909091); fWeights[6] = 0.011645249086029;
		fPoints.PutVal(7, 0, 0.090909090909091);  fPoints.PutVal(7, 1, 0.727272727272727); fPoints.PutVal(7, 2, 0.090909090909091); fWeights[7] = 0.011645249086029;
		fPoints.PutVal(8, 0, 0.090909090909091);  fPoints.PutVal(8, 1, 0.090909090909091); fPoints.PutVal(8, 2, 0.727272727272727); fWeights[8] = 0.011645249086029;
		fPoints.PutVal(9, 0, 0.433449846426336);  fPoints.PutVal(9, 1, 0.066550153573664); fPoints.PutVal(9, 2, 0.066550153573664); fWeights[9] = 0.010949141561386;
		fPoints.PutVal(10, 0, 0.066550153573664);  fPoints.PutVal(10, 1, 0.433449846426336); fPoints.PutVal(10, 2, 0.066550153573664); fWeights[10] = 0.010949141561386;
		fPoints.PutVal(11, 0, 0.066550153573664);  fPoints.PutVal(11, 1, 0.066550153573664); fPoints.PutVal(11, 2, 0.433449846426336); fWeights[11] = 0.010949141561386;
		fPoints.PutVal(12, 0, 0.066550153573664);  fPoints.PutVal(12, 1, 0.433449846426336); fPoints.PutVal(12, 2, 0.433449846426336); fWeights[12] = 0.010949141561386;
		fPoints.PutVal(13, 0, 0.433449846426336);  fPoints.PutVal(13, 1, 0.066550153573664); fPoints.PutVal(13, 2, 0.433449846426336); fWeights[13] = 0.010949141561386;
		fPoints.PutVal(14, 0, 0.433449846426336);  fPoints.PutVal(14, 1, 0.433449846426336); fPoints.PutVal(14, 2, 0.066550153573664); fWeights[14] = 0.010949141561386;
	}

	co.resize(3);

	co[0] = fPoints.GetVal(p, 0);
	co[1] = fPoints.GetVal(p, 1);
	co[2] = fPoints.GetVal(p, 2);
	weight = fWeights[p];
}