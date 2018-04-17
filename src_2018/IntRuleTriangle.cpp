/*
*  IntRuleTriangle.cpp
*
*  Created by Leandro Valdez on 5/4/18.
*
*/

#include <iomanip>
#include <math.h>
#include "IntRuleTriangle.h"
#include "tpanic.h"

IntRuleTriangle::IntRuleTriangle() :IntRule() {}

IntRuleTriangle::IntRuleTriangle(int order) : IntRule(order) {}

int IntRuleTriangle::NPoints() const
{
	int npoints;

	if (fOrder<0 || fOrder > 19)
	{
		DebugStop();
	}

	if (fOrder == 0) {

		npoints = 1;
	}

	if (fOrder == 1 || fOrder == 2) {

		npoints = 3;
	}

	if (fOrder == 3) {

		npoints = 6;
	}

	if (fOrder == 4) {

		npoints = 6;
	}

	if (fOrder == 5) {

		npoints = 7;
	}

	if (fOrder == 6) {

		npoints = 12;
	}
	
	if (fOrder == 7) {

		npoints = 15;
	}

	if (fOrder == 8) {

		npoints = 16;
	}

	if (fOrder == 9) {

		npoints = 19;
	}

	if (fOrder == 10) {

		npoints = 25;
	}

	if (fOrder == 11) {

		npoints = 28;
	}

	if (fOrder == 12) {

		npoints = 33;
	}

	if (fOrder == 13) {

		npoints = 37;
	}

	if (fOrder == 14) {

		npoints = 46;
	}

	if (fOrder == 15) {

		npoints = 52;
	}

	if (fOrder == 16) {

		npoints = 55;
	}

	if (fOrder == 17) {

		npoints = 61;
	}

	if (fOrder == 18) {

		npoints = 72;
	}

	if (fOrder == 19) {

		npoints = 73;
	}

	return npoints;
}

void IntRuleTriangle::Print(std::ostream &out) const
{
	out << "ORDER	" << fOrder << "	NPoints	" << NPoints() << "\n" << std::endl;

	for (int i = 0; i < NPoints(); i++)
	{
		VecDouble co(NPoints());
		double weight;
		IntRuleTriangle T(fOrder);
		T.Point(i, co, weight);
		std::cout << std::setprecision(12) << std::fixed;
		out << "POINT	" << i << "	POS {" << co[0] << ", " << co[1]
			<< "}	WEIGHT " << weight << std::endl;
	}
}

void IntRuleTriangle::Point(int p, VecDouble &co, double &weight)
{
	if (p<0 || p >= NPoints())
	{
		DebugStop();
	}

	if (fOrder == 0) {

		fPoints.Resize(1, 2);
		fWeights.resize(1);

		fPoints.PutVal(0, 0, 0.33333333333333331);  fPoints.PutVal(0, 1, 0.33333333333333331);  fWeights[0] = 0.5;
	}
	
	if (fOrder == 1 || fOrder == 2) {

		fPoints.Resize(3, 2);
		fWeights.resize(3);

		fPoints.PutVal(0, 0, 0.16666666666666666);  fPoints.PutVal(0, 1, 0.66666666666666663);  fWeights[0] = 0.16666666666666666;
		fPoints.PutVal(1, 0, 0.66666666666666663);  fPoints.PutVal(1, 1, 0.16666666666666666);  fWeights[1] = 0.16666666666666666;
		fPoints.PutVal(2, 0, 0.16666666666666666);  fPoints.PutVal(2, 1, 0.16666666666666666);  fWeights[2] = 0.16666666666666666;
	}

	if (fOrder == 3) {

		fPoints.Resize(6, 2);
		fWeights.resize(6);

		fPoints.PutVal(0, 0, 0.1628828503958919);  fPoints.PutVal(0, 1, 0.6742342992082162);      fWeights[0] = 0.14057490122048982;
		fPoints.PutVal(1, 0, 0.6742342992082162);  fPoints.PutVal(1, 1, 0.1628828503958919);      fWeights[1] = 0.14057490122048982;
		fPoints.PutVal(2, 0, 0.1628828503958919);  fPoints.PutVal(2, 1, 0.1628828503958919);      fWeights[2] = 0.14057490122048982;
		fPoints.PutVal(3, 0, 0.47791988356756371);  fPoints.PutVal(3, 1, 0.044160232864872598);   fWeights[3] = 0.026091765446176841;
		fPoints.PutVal(4, 0, 0.044160232864872598);  fPoints.PutVal(4, 1, 0.47791988356756371);   fWeights[4] = 0.026091765446176841;
		fPoints.PutVal(5, 0, 0.47791988356756371);  fPoints.PutVal(5, 1, 0.47791988356756371);    fWeights[5] = 0.026091765446176841;
	}

	if (fOrder == 4) {

		fPoints.Resize(6, 2);
		fWeights.resize(6);

		fPoints.PutVal(0, 0, 0.44594849091596489);  fPoints.PutVal(0, 1, 0.10810301816807023);      fWeights[0] = 0.11169079483900574;
		fPoints.PutVal(1, 0, 0.10810301816807023);  fPoints.PutVal(1, 1, 0.44594849091596489);      fWeights[1] = 0.11169079483900574;
		fPoints.PutVal(2, 0, 0.44594849091596489);  fPoints.PutVal(2, 1, 0.44594849091596489);      fWeights[2] = 0.11169079483900574;
		fPoints.PutVal(3, 0, 0.091576213509770743);  fPoints.PutVal(3, 1, 0.81684757298045851);      fWeights[3] = 0.054975871827660935;
		fPoints.PutVal(4, 0, 0.81684757298045851);  fPoints.PutVal(4, 1, 0.091576213509770743);      fWeights[4] = 0.054975871827660935;
		fPoints.PutVal(5, 0, 0.091576213509770743);  fPoints.PutVal(5, 1, 0.091576213509770743);      fWeights[5] = 0.054975871827660935;

	}

	if (fOrder == 5) {

		fPoints.Resize(7, 2);
		fWeights.resize(7);

		fPoints.PutVal(0, 0, 0.10128650732345634);  fPoints.PutVal(0, 1, 0.79742698535308731);      fWeights[0] = 0.06296959027241357;
		fPoints.PutVal(1, 0, 0.79742698535308731);  fPoints.PutVal(1, 1, 0.10128650732345634);      fWeights[1] = 0.06296959027241357;
		fPoints.PutVal(2, 0, 0.10128650732345634);  fPoints.PutVal(2, 1, 0.10128650732345634);      fWeights[2] = 0.06296959027241357;
		fPoints.PutVal(3, 0, 0.47014206410511511);  fPoints.PutVal(3, 1, 0.059715871789769823);      fWeights[3] = 0.066197076394253096;
		fPoints.PutVal(4, 0, 0.059715871789769823);  fPoints.PutVal(4, 1, 0.47014206410511511);      fWeights[4] = 0.066197076394253096;
		fPoints.PutVal(5, 0, 0.47014206410511511);  fPoints.PutVal(5, 1, 0.47014206410511511);       fWeights[5] = 0.066197076394253096;
		fPoints.PutVal(6, 0, 0.33333333333333331);  fPoints.PutVal(6, 1, 0.33333333333333331);       fWeights[6] = 0.1125;
	}

	if (fOrder == 6) {

		fPoints.Resize(12, 2);
		fWeights.resize(12);

		fPoints.PutVal(0, 0, 0.063089014491502227);    fPoints.PutVal(0, 1, 0.87382197101699555);         fWeights[0] = 0.025422453185103409;
		fPoints.PutVal(1, 0, 0.87382197101699555);     fPoints.PutVal(1, 1, 0.063089014491502227);        fWeights[1] = 0.025422453185103409;
		fPoints.PutVal(2, 0, 0.063089014491502227);    fPoints.PutVal(2, 1, 0.063089014491502227);        fWeights[2] = 0.025422453185103409;
		fPoints.PutVal(3, 0, 0.24928674517091043);     fPoints.PutVal(3, 1, 0.50142650965817914);         fWeights[3] = 0.058393137863189684;
		fPoints.PutVal(4, 0, 0.50142650965817914);     fPoints.PutVal(4, 1, 0.24928674517091043);         fWeights[4] = 0.058393137863189684;
		fPoints.PutVal(5, 0, 0.24928674517091043);     fPoints.PutVal(5, 1, 0.24928674517091043);         fWeights[5] = 0.058393137863189684;
		fPoints.PutVal(6, 0, 0.31035245103378439);     fPoints.PutVal(6, 1, 0.63650249912139867);         fWeights[6] = 0.041425537809186785;
		fPoints.PutVal(7, 0, 0.63650249912139867);     fPoints.PutVal(7, 1, 0.31035245103378439);         fWeights[7] = 0.041425537809186785;
		fPoints.PutVal(8, 0, 0.053145049844816945);    fPoints.PutVal(8, 1, 0.63650249912139867);         fWeights[8] = 0.041425537809186785;
		fPoints.PutVal(9, 0, 0.63650249912139867);     fPoints.PutVal(9, 1, 0.053145049844816945);        fWeights[9] = 0.041425537809186785;
		fPoints.PutVal(10, 0, 0.053145049844816945);   fPoints.PutVal(10, 1, 0.31035245103378439);        fWeights[10] = 0.041425537809186785;
		fPoints.PutVal(11, 0, 0.31035245103378439);    fPoints.PutVal(11, 1, 0.053145049844816945);       fWeights[11] = 0.041425537809186785;
	}


	if (fOrder == 7) {

		fPoints.Resize(15, 2);
		fWeights.resize(15);

		fPoints.PutVal(0, 0, 0.028263924156076339);    fPoints.PutVal(0, 1, 0.94347215168784737);         fWeights[0] = 0.0067669312578327806;
		fPoints.PutVal(1, 0, 0.94347215168784737);     fPoints.PutVal(1, 1, 0.028263924156076339);        fWeights[1] = 0.0067669312578327806;
		fPoints.PutVal(2, 0, 0.028263924156076339);    fPoints.PutVal(2, 1, 0.028263924156076339);        fWeights[2] = 0.0067669312578327806;

		fPoints.PutVal(3, 0, 0.47431132326722258);     fPoints.PutVal(3, 1, 0.051377353465554852);         fWeights[3] = 0.039475627216005491;
		fPoints.PutVal(4, 0, 0.051377353465554852);     fPoints.PutVal(4, 1, 0.47431132326722258);         fWeights[4] = 0.039475627216005491;
		fPoints.PutVal(5, 0, 0.47431132326722258);     fPoints.PutVal(5, 1, 0.47431132326722258);         fWeights[5] = 0.039475627216005491;

		fPoints.PutVal(6, 0, 0.24114332584984882);     fPoints.PutVal(6, 1, 0.51771334830030236);         fWeights[6] = 0.064303963909453032;
		fPoints.PutVal(7, 0, 0.51771334830030236);     fPoints.PutVal(7, 1, 0.24114332584984882);         fWeights[7] = 0.064303963909453032;
		fPoints.PutVal(8, 0, 0.24114332584984882);    fPoints.PutVal(8, 1, 0.24114332584984882);         fWeights[8] = 0.064303963909453032;

		fPoints.PutVal(9, 0, 0.04627087779880891);     fPoints.PutVal(9, 1, 0.1925063741766673);        fWeights[9] = 0.028060072141687677;
		fPoints.PutVal(10, 0, 0.1925063741766673);     fPoints.PutVal(10, 1, 0.04627087779880891);        fWeights[10] = 0.028060072141687677;
		fPoints.PutVal(11, 0, 0.76122274802452383);    fPoints.PutVal(11, 1, 0.1925063741766673);       fWeights[11] = 0.028060072141687677;

		fPoints.PutVal(12, 0, 0.1925063741766673);    fPoints.PutVal(12, 1, 0.76122274802452383);        fWeights[12] = 0.028060072141687677;
		fPoints.PutVal(13, 0, 0.76122274802452383);   fPoints.PutVal(13, 1, 0.04627087779880891);        fWeights[13] = 0.028060072141687677;
		fPoints.PutVal(14, 0, 0.04627087779880891);    fPoints.PutVal(14, 1, 0.76122274802452383);       fWeights[14] = 0.028060072141687677;
	}
	
	if (fOrder == 8) {

		fPoints.Resize(16, 2);
		fWeights.resize(16);

		fPoints.PutVal(0, 0, 0.33333333333333331);      fPoints.PutVal(0, 1, 0.33333333333333331);    fWeights[0] = 0.072157803838893586;
		fPoints.PutVal(1, 0, 0.17056930775176021);      fPoints.PutVal(1, 1, 0.65886138449647957);    fWeights[1] = 0.051608685267359122;
		fPoints.PutVal(2, 0, 0.65886138449647957);      fPoints.PutVal(2, 1, 0.17056930775176021);    fWeights[2] = 0.051608685267359122;
		fPoints.PutVal(3, 0, 0.17056930775176021);      fPoints.PutVal(3, 1, 0.17056930775176021);    fWeights[3] = 0.051608685267359122;
		fPoints.PutVal(4, 0, 0.050547228317030977);     fPoints.PutVal(4, 1, 0.89890554336593809);    fWeights[4] = 0.01622924881159904;
		fPoints.PutVal(5, 0, 0.89890554336593809);      fPoints.PutVal(5, 1, 0.050547228317030977);   fWeights[5] = 0.01622924881159904;
		fPoints.PutVal(6, 0, 0.050547228317030977);     fPoints.PutVal(6, 1, 0.050547228317030977);   fWeights[6] = 0.01622924881159904;
		fPoints.PutVal(7, 0, 0.45929258829272318);      fPoints.PutVal(7, 1, 0.081414823414553694);   fWeights[7] = 0.04754581713364231;
		fPoints.PutVal(8, 0, 0.081414823414553694);     fPoints.PutVal(8, 1, 0.45929258829272318);    fWeights[8] = 0.04754581713364231;
		fPoints.PutVal(9, 0, 0.45929258829272318);      fPoints.PutVal(9, 1, 0.45929258829272318);    fWeights[9] = 0.04754581713364231;
		fPoints.PutVal(10, 0, 0.0083947774099576052);   fPoints.PutVal(10, 1, 0.72849239295540424);    fWeights[10] = 0.013615157087217496;
		fPoints.PutVal(11, 0, 0.72849239295540424);     fPoints.PutVal(11, 1, 0.0083947774099576052);  fWeights[11] = 0.013615157087217496;
		fPoints.PutVal(12, 0, 0.26311282963463811);     fPoints.PutVal(12, 1, 0.72849239295540424);    fWeights[12] = 0.013615157087217496;
		fPoints.PutVal(13, 0, 0.72849239295540424);     fPoints.PutVal(13, 1, 0.26311282963463811);    fWeights[13] = 0.013615157087217496;
		fPoints.PutVal(14, 0, 0.26311282963463811);     fPoints.PutVal(14, 1, 0.0083947774099576052);  fWeights[14] = 0.013615157087217496;
		fPoints.PutVal(15, 0, 0.0083947774099576052);   fPoints.PutVal(15, 1, 0.26311282963463811);    fWeights[15] = 0.013615157087217496;
	}

	if (fOrder == 9) {

		fPoints.Resize(19, 2);
		fWeights.resize(19);

		fPoints.PutVal(0, 0, 0.33333333333333331);         fPoints.PutVal(0, 1, 0.33333333333333331);      fWeights[0] = 0.048567898141399418;
		fPoints.PutVal(1, 0, 0.48968251919873762);         fPoints.PutVal(1, 1, 0.020634961602524746);     fWeights[1] = 0.015667350113569536;
		fPoints.PutVal(2, 0, 0.020634961602524746);        fPoints.PutVal(2, 1, 0.48968251919873762);      fWeights[2] = 0.015667350113569536;
		fPoints.PutVal(3, 0, 0.48968251919873762);         fPoints.PutVal(3, 1, 0.48968251919873762);      fWeights[3] = 0.015667350113569536;
		fPoints.PutVal(4, 0, 0.044729513394452712);        fPoints.PutVal(4, 1, 0.91054097321109462);      fWeights[4] = 0.012788837829349016;
		fPoints.PutVal(5, 0, 0.91054097321109462);         fPoints.PutVal(5, 1, 0.044729513394452712);     fWeights[5] = 0.012788837829349016;
		fPoints.PutVal(6, 0, 0.044729513394452712);        fPoints.PutVal(6, 1, 0.044729513394452712);     fWeights[6] = 0.012788837829349016;
		fPoints.PutVal(7, 0, 0.43708959149293664);         fPoints.PutVal(7, 1, 0.12582081701412673);      fWeights[7] = 0.038913770502387139;
		fPoints.PutVal(8, 0, 0.12582081701412673);         fPoints.PutVal(8, 1, 0.43708959149293664);      fWeights[8] = 0.038913770502387139;
		fPoints.PutVal(9, 0, 0.43708959149293664);         fPoints.PutVal(9, 1, 0.43708959149293664);      fWeights[9] = 0.038913770502387139;
		fPoints.PutVal(10, 0, 0.18820353561903272);        fPoints.PutVal(10, 1, 0.62359292876193451);     fWeights[10] = 0.039823869463605124;
		fPoints.PutVal(11, 0, 0.62359292876193451);        fPoints.PutVal(11, 1, 0.18820353561903272);     fWeights[11] = 0.039823869463605124;
		fPoints.PutVal(12, 0, 0.18820353561903272);        fPoints.PutVal(12, 1, 0.18820353561903272);     fWeights[12] = 0.039823869463605124;
		fPoints.PutVal(13, 0, 0.22196298916076571);        fPoints.PutVal(13, 1, 0.036838412054736286);    fWeights[13] = 0.021641769688644688;
		fPoints.PutVal(14, 0, 0.036838412054736286);       fPoints.PutVal(14, 1, 0.22196298916076571);     fWeights[14] = 0.021641769688644688;
		fPoints.PutVal(15, 0, 0.74119859878449801);        fPoints.PutVal(15, 1, 0.036838412054736286);    fWeights[15] = 0.021641769688644688;
		fPoints.PutVal(16, 0, 0.036838412054736286);       fPoints.PutVal(16, 1, 0.74119859878449801);     fWeights[16] = 0.021641769688644688;
		fPoints.PutVal(17, 0, 0.74119859878449801);        fPoints.PutVal(17, 1, 0.22196298916076571);     fWeights[17] = 0.021641769688644688;
		fPoints.PutVal(18, 0, 0.22196298916076571);        fPoints.PutVal(18, 1, 0.74119859878449801);     fWeights[18] = 0.021641769688644688;
	}
	
	if (fOrder == 10) {

		fPoints.Resize(25, 2);
		fWeights.resize(25);

		fPoints.PutVal(0, 0, 0.33333333333333331);     fPoints.PutVal(0, 1, 0.33333333333333331);      fWeights[0] = 0.040468714398811438;
		fPoints.PutVal(1, 0, 0.42727317884677551);     fPoints.PutVal(1, 1, 0.14545364230644892);      fWeights[1] = 0.038649294001481559;
		fPoints.PutVal(2, 0, 0.14545364230644892);      fPoints.PutVal(2, 1, 0.42727317884677551);      fWeights[2] = 0.038649294001481559;
		fPoints.PutVal(3, 0, 0.42727317884677551);     fPoints.PutVal(3, 1, 0.42727317884677551);      fWeights[3] = 0.038649294001481559;
		fPoints.PutVal(4, 0, 0.18309922244867502);      fPoints.PutVal(4, 1, 0.63380155510264991);      fWeights[4] = 0.039228819306185866;
		fPoints.PutVal(5, 0, 0.63380155510264991);     fPoints.PutVal(5, 1, 0.18309922244867502);      fWeights[5] = 0.039228819306185866;
		fPoints.PutVal(6, 0, 0.18309922244867502);     fPoints.PutVal(6, 1, 0.18309922244867502);      fWeights[6] = 0.039228819306185866;
		fPoints.PutVal(7, 0, 0.4904340197011306);      fPoints.PutVal(7, 1, 0.019131960597738824);     fWeights[7] = 0.0087345839979647427;
		fPoints.PutVal(8, 0, 0.019131960597738824);    fPoints.PutVal(8, 1, 0.4904340197011306);       fWeights[8] = 0.0087345839979647427;
		fPoints.PutVal(9, 0, 0.4904340197011306);      fPoints.PutVal(9, 1, 0.4904340197011306);       fWeights[9] = 0.0087345839979647427;
		fPoints.PutVal(10, 0, 0.012572445551580533);   fPoints.PutVal(10, 1, 0.97485510889683891);     fWeights[10] = 0.0021461870924164139;
		fPoints.PutVal(11, 0, 0.97485510889683891);    fPoints.PutVal(11, 1, 0.012572445551580533);    fWeights[11] = 0.0021461870924164139;
		fPoints.PutVal(12, 0, 0.012572445551580533);   fPoints.PutVal(12, 1, 0.012572445551580533);    fWeights[12] = 0.0021461870924164139;
		fPoints.PutVal(13, 0, 0.30804600168524771);    fPoints.PutVal(13, 1, 0.037685330394686162);    fWeights[13] = 0.018734429105233822;
		fPoints.PutVal(14, 0, 0.037685330394686162);   fPoints.PutVal(14, 1, 0.30804600168524771);     fWeights[14] = 0.018734429105233822;
		fPoints.PutVal(15, 0, 0.6542686679200661);     fPoints.PutVal(15, 1, 0.037685330394686162);     fWeights[15] = 0.018734429105233822;
		fPoints.PutVal(16, 0, 0.037685330394686162);   fPoints.PutVal(16, 1, 0.6542686679200661);      fWeights[16] = 0.018734429105233822;
		fPoints.PutVal(17, 0, 0.6542686679200661);     fPoints.PutVal(17, 1, 0.30804600168524771);     fWeights[17] = 0.018734429105233822;
		fPoints.PutVal(18, 0, 0.30804600168524771);    fPoints.PutVal(18, 1, 0.6542686679200661);      fWeights[18] = 0.018734429105233822;
		fPoints.PutVal(19, 0, 0.033371833739304788); 	fPoints.PutVal(19, 1, 0.84382358919213596);     fWeights[19] = 0.013474676295939981;
		fPoints.PutVal(20, 0, 0.84382358919213596); 	fPoints.PutVal(20, 1, 0.033371833739304788);    fWeights[20] = 0.013474676295939981;
		fPoints.PutVal(21, 0, 0.12280457706855927); 	fPoints.PutVal(21, 1, 0.84382358919213596);     fWeights[21] = 0.013474676295939981;
		fPoints.PutVal(22, 0, 0.84382358919213596); 	fPoints.PutVal(22, 1, 0.12280457706855927);     fWeights[22] = 0.013474676295939981;
		fPoints.PutVal(23, 0, 0.12280457706855927); 	fPoints.PutVal(23, 1, 0.033371833739304788);    fWeights[23] = 0.013474676295939981;
		fPoints.PutVal(24, 0, 0.033371833739304788);   fPoints.PutVal(24, 1, 0.12280457706855927);      fWeights[24] = 0.013474676295939981;
	}
	
	if (fOrder == 11) {

		fPoints.Resize(28, 2);
		fWeights.resize(28);

		fPoints.PutVal(0, 0, 0.33333333333333331);     fPoints.PutVal(0, 1, 0.33333333333333331);      fWeights[0] = 0.040588980148433582;
		fPoints.PutVal(1, 0, 0.030938355245430784);    fPoints.PutVal(1, 1, 0.93812328950913848);      fWeights[1] = 0.0061620217534547467;
		fPoints.PutVal(2, 0, 0.93812328950913848);     fPoints.PutVal(2, 1, 0.030938355245430784);     fWeights[2] = 0.0061620217534547467;
		fPoints.PutVal(3, 0, 0.030938355245430784);    fPoints.PutVal(3, 1, 0.030938355245430784);     fWeights[3] = 0.0061620217534547467;
		fPoints.PutVal(4, 0, 0.43649818113412886);      fPoints.PutVal(4, 1, 0.12700363773174231);      fWeights[4] = 0.031414004872205054;
		fPoints.PutVal(5, 0, 0.12700363773174231);     fPoints.PutVal(5, 1, 0.43649818113412886);      fWeights[5] = 0.031414004872205054;
		fPoints.PutVal(6, 0, 0.43649818113412886);     fPoints.PutVal(6, 1, 0.43649818113412886);      fWeights[6] = 0.031414004872205054;
		fPoints.PutVal(7, 0, 0.49898476370259326);     fPoints.PutVal(7, 1, 0.0020304725948134673);    fWeights[7] = 0.0061101895246822649;
		fPoints.PutVal(8, 0, 0.0020304725948134673);   fPoints.PutVal(8, 1, 0.49898476370259326);      fWeights[8] = 0.0061101895246822649;
		fPoints.PutVal(9, 0, 0.49898476370259326);     fPoints.PutVal(9, 1, 0.49898476370259326);      fWeights[9] = 0.0061101895246822649;
		fPoints.PutVal(10, 0, 0.21468819795859434);    fPoints.PutVal(10, 1, 0.57062360408281132);      fWeights[10] = 0.033850674476405752;
		fPoints.PutVal(11, 0, 0.57062360408281132);    fPoints.PutVal(11, 1, 0.21468819795859434);      fWeights[11] = 0.033850674476405752;
		fPoints.PutVal(12, 0, 0.21468819795859434); 	fPoints.PutVal(12, 1, 0.21468819795859434);      fWeights[12] = 0.033850674476405752;
		fPoints.PutVal(13, 0, 0.11368310404211339);    fPoints.PutVal(13, 1, 0.77263379191577319);      fWeights[13] = 0.020109846814425847;
		fPoints.PutVal(14, 0, 0.77263379191577319);    fPoints.PutVal(14, 1, 0.11368310404211339);      fWeights[14] = 0.020109846814425847;
		fPoints.PutVal(15, 0, 0.11368310404211339);    fPoints.PutVal(15, 1, 0.11368310404211339);      fWeights[15] = 0.020109846814425847;
		fPoints.PutVal(16, 0, 0.15974230459185018);    fPoints.PutVal(16, 1, 0.014638929243286906);     fWeights[16] = 0.0073811363588580509;
		fPoints.PutVal(17, 0, 0.014638929243286906);   fPoints.PutVal(17, 1, 0.15974230459185018);      fWeights[17] = 0.0073811363588580509;
		fPoints.PutVal(18, 0, 0.82561876616486285);    fPoints.PutVal(18, 1, 0.014638929243286906);     fWeights[18] = 0.0073811363588580509;
		fPoints.PutVal(19, 0, 0.014638929243286906);   fPoints.PutVal(19, 1, 0.82561876616486285);      fWeights[19] = 0.0073811363588580509;
		fPoints.PutVal(20, 0, 0.82561876616486285);    fPoints.PutVal(20, 1, 0.15974230459185018);      fWeights[20] = 0.0073811363588580509;
		fPoints.PutVal(21, 0, 0.15974230459185018);    fPoints.PutVal(21, 1, 0.82561876616486285);      fWeights[21] = 0.0073811363588580509;
		fPoints.PutVal(22, 0, 0.31178371570959901);    fPoints.PutVal(22, 1, 0.047743974155535732);     fWeights[22] = 0.02036399822914952;
		fPoints.PutVal(23, 0, 0.047743974155535732);   fPoints.PutVal(23, 1, 0.31178371570959901);      fWeights[23] = 0.02036399822914952;
		fPoints.PutVal(24, 0, 0.64047231013486527);    fPoints.PutVal(24, 1, 0.047743974155535732);     fWeights[24] = 0.02036399822914952;
		fPoints.PutVal(25, 0, 0.047743974155535732);   fPoints.PutVal(25, 1, 0.64047231013486527);      fWeights[25] = 0.02036399822914952;
		fPoints.PutVal(26, 0, 0.64047231013486527);    fPoints.PutVal(26, 1, 0.31178371570959901);      fWeights[26] = 0.02036399822914952;
		fPoints.PutVal(27, 0, 0.31178371570959901); 	fPoints.PutVal(27, 1, 0.64047231013486527);      fWeights[27] = 0.02036399822914952;
	}
	
	if (fOrder == 12) {

		fPoints.Resize(33, 2);
		fWeights.resize(33);

		fPoints.PutVal(0, 0, 0.021317350453210371);    fPoints.PutVal(0, 1, 0.95736529909357926);      fWeights[0] = 0.0030831305257795088;
		fPoints.PutVal(1, 0, 0.95736529909357926);     fPoints.PutVal(1, 1, 0.021317350453210371);     fWeights[1] = 0.0030831305257795088;
		fPoints.PutVal(2, 0, 0.021317350453210371);    fPoints.PutVal(2, 1, 0.021317350453210371);     fWeights[2] = 0.0030831305257795088;
		fPoints.PutVal(3, 0, 0.27121038501211592);      fPoints.PutVal(3, 1, 0.45757922997576816);      fWeights[3] = 0.031429112108942552;
		fPoints.PutVal(4, 0, 0.45757922997576816);     fPoints.PutVal(4, 1, 0.27121038501211592);      fWeights[4] = 0.031429112108942552;
		fPoints.PutVal(5, 0, 0.27121038501211592);     fPoints.PutVal(5, 1, 0.27121038501211592);      fWeights[5] = 0.031429112108942552;
		fPoints.PutVal(6, 0, 0.12757614554158592);     fPoints.PutVal(6, 1, 0.74484770891682817);      fWeights[6] = 0.017398056465354472;
		fPoints.PutVal(7, 0, 0.74484770891682817);     fPoints.PutVal(7, 1, 0.12757614554158592);      fWeights[7] = 0.017398056465354472;
		fPoints.PutVal(8, 0, 0.12757614554158592);     fPoints.PutVal(8, 1, 0.12757614554158592);      fWeights[8] = 0.017398056465354472;
		fPoints.PutVal(9, 0, 0.43972439229446025);     fPoints.PutVal(9, 1, 0.12055121541107945);      fWeights[9] = 0.021846272269019203;
		fPoints.PutVal(10, 0, 0.12055121541107945);    fPoints.PutVal(10, 1, 0.43972439229446025);      fWeights[10] = 0.021846272269019203;
		fPoints.PutVal(11, 0, 0.43972439229446025);    fPoints.PutVal(11, 1, 0.43972439229446025);      fWeights[11] = 0.021846272269019203;
		fPoints.PutVal(12, 0, 0.48821738977380486);    fPoints.PutVal(12, 1, 0.023565220452390234);     fWeights[12] = 0.012865533220227668;
		fPoints.PutVal(13, 0, 0.023565220452390234);   fPoints.PutVal(13, 1, 0.48821738977380486);      fWeights[13] = 0.012865533220227668;
		fPoints.PutVal(14, 0, 0.48821738977380486);    fPoints.PutVal(14, 1, 0.48821738977380486);      fWeights[14] = 0.012865533220227668;
		fPoints.PutVal(15, 0, 0.28132558098993954);    fPoints.PutVal(15, 1, 0.022838332222257028);     fWeights[15] = 0.011178386601151722;
		fPoints.PutVal(16, 0, 0.022838332222257028);   fPoints.PutVal(16, 1, 0.28132558098993954);      fWeights[16] = 0.011178386601151722;
		fPoints.PutVal(17, 0, 0.6958360867878034);     fPoints.PutVal(17, 1, 0.022838332222257028);     fWeights[17] = 0.011178386601151722;
		fPoints.PutVal(18, 0, 0.022838332222257028); 	fPoints.PutVal(18, 1, 0.6958360867878034);       fWeights[18] = 0.011178386601151722;
		fPoints.PutVal(19, 0, 0.6958360867878034);     fPoints.PutVal(19, 1, 0.28132558098993954);      fWeights[19] = 0.011178386601151722;
		fPoints.PutVal(20, 0, 0.28132558098993954);    fPoints.PutVal(20, 1, 0.6958360867878034);       fWeights[20] = 0.011178386601151722;
		fPoints.PutVal(21, 0, 0.11625191590759715); 	fPoints.PutVal(21, 1, 0.02573405054833023);      fWeights[21] = 0.0086581155543294461;
		fPoints.PutVal(22, 0, 0.02573405054833023); 	fPoints.PutVal(22, 1, 0.11625191590759715);      fWeights[22] = 0.0086581155543294461;
		fPoints.PutVal(23, 0, 0.85801403354407269);    fPoints.PutVal(23, 1, 0.02573405054833023);      fWeights[23] = 0.0086581155543294461;
		fPoints.PutVal(24, 0, 0.02573405054833023);    fPoints.PutVal(24, 1, 0.85801403354407269);      fWeights[24] = 0.0086581155543294461;
		fPoints.PutVal(25, 0, 0.85801403354407269);    fPoints.PutVal(25, 1, 0.11625191590759715);      fWeights[25] = 0.0086581155543294461;
		fPoints.PutVal(26, 0, 0.11625191590759715);    fPoints.PutVal(26, 1, 0.85801403354407269);      fWeights[26] = 0.0086581155543294461;
		fPoints.PutVal(27, 0, 0.27571326968551418); 	fPoints.PutVal(27, 1, 0.115343494534698);        fWeights[27] = 0.020185778883190463;
		fPoints.PutVal(28, 0, 0.115343494534698);      fPoints.PutVal(28, 1, 0.27571326968551418);      fWeights[28] = 0.020185778883190463;
		fPoints.PutVal(29, 0, 0.60894323577978782);    fPoints.PutVal(29, 1, 0.115343494534698);        fWeights[29] = 0.020185778883190463;
		fPoints.PutVal(30, 0, 0.115343494534698);      fPoints.PutVal(30, 1, 0.60894323577978782);      fWeights[30] = 0.020185778883190463;
		fPoints.PutVal(31, 0, 0.60894323577978782);    fPoints.PutVal(31, 1, 0.27571326968551418);      fWeights[31] = 0.020185778883190463;
		fPoints.PutVal(32, 0, 0.27571326968551418);    fPoints.PutVal(32, 1, 0.60894323577978782);      fWeights[32] = 0.020185778883190463;
	}
	
	if (fOrder == 13) {

		fPoints.Resize(37, 2);
		fWeights.resize(37);

		fPoints.PutVal(0, 0, 0.33333333333333331);     fPoints.PutVal(0, 1, 0.33333333333333331);      fWeights[0] = 0.03398001829341582;
		fPoints.PutVal(1, 0, 0.42694141425980042);     fPoints.PutVal(1, 1, 0.14611717148039918);      fWeights[1] = 0.027800983765226665;
		fPoints.PutVal(2, 0, 0.14611717148039918);     fPoints.PutVal(2, 1, 0.42694141425980042);      fWeights[2] = 0.027800983765226665;
		fPoints.PutVal(3, 0, 0.42694141425980042);     fPoints.PutVal(3, 1, 0.42694141425980042);      fWeights[3] = 0.027800983765226665;
		fPoints.PutVal(4, 0, 0.22137228629183289); 	fPoints.PutVal(4, 1, 0.55725542741633416);      fWeights[4] = 0.029139242559599991;
		fPoints.PutVal(5, 0, 0.55725542741633416);     fPoints.PutVal(5, 1, 0.22137228629183289);      fWeights[5] = 0.029139242559599991;
		fPoints.PutVal(6, 0, 0.22137228629183289);     fPoints.PutVal(6, 1, 0.22137228629183289);      fWeights[6] = 0.029139242559599991;
		fPoints.PutVal(7, 0, 0.021509681108843184);    fPoints.PutVal(7, 1, 0.95698063778231368);      fWeights[7] = 0.0030261685517695858;
		fPoints.PutVal(8, 0, 0.95698063778231368);     fPoints.PutVal(8, 1, 0.021509681108843184);     fWeights[8] = 0.0030261685517695858;
		fPoints.PutVal(9, 0, 0.021509681108843184);    fPoints.PutVal(9, 1, 0.021509681108843184);     fWeights[9] = 0.0030261685517695858;
		fPoints.PutVal(10, 0, 0.48907694645253935);    fPoints.PutVal(10, 1, 0.0218461070949213);      fWeights[10] = 0.011997200964447365;
		fPoints.PutVal(11, 0, 0.0218461070949213); 	fPoints.PutVal(11, 1, 0.48907694645253935);     fWeights[11] = 0.011997200964447365;
		fPoints.PutVal(12, 0, 0.48907694645253935);    fPoints.PutVal(12, 1, 0.48907694645253935);     fWeights[12] = 0.011997200964447365;
		fPoints.PutVal(13, 0, 0.30844176089211778);    fPoints.PutVal(13, 1, 0.068012243554206653);    fWeights[13] = 0.017320638070424187;
		fPoints.PutVal(14, 0, 0.068012243554206653);   fPoints.PutVal(14, 1, 0.30844176089211778);     fWeights[14] = 0.017320638070424187;
		fPoints.PutVal(15, 0, 0.62354599555367562); 	fPoints.PutVal(15, 1, 0.068012243554206653);    fWeights[15] = 0.017320638070424187;
		fPoints.PutVal(16, 0, 0.068012243554206653);   fPoints.PutVal(16, 1, 0.62354599555367562);     fWeights[16] = 0.017320638070424187;
		fPoints.PutVal(17, 0, 0.62354599555367562);    fPoints.PutVal(17, 1, 0.30844176089211778);     fWeights[17] = 0.017320638070424187;
		fPoints.PutVal(18, 0, 0.30844176089211778);    fPoints.PutVal(18, 1, 0.62354599555367562);     fWeights[18] = 0.017320638070424187;
		fPoints.PutVal(19, 0, 0.11092204280346339);    fPoints.PutVal(19, 1, 0.02437018690109383);     fWeights[19] = 0.0074827005525828338;
		fPoints.PutVal(20, 0, 0.02437018690109383); 	fPoints.PutVal(20, 1, 0.11092204280346339);     fWeights[20] = 0.0074827005525828338;
		fPoints.PutVal(21, 0, 0.86470777029544277); 	fPoints.PutVal(21, 1, 0.02437018690109383);     fWeights[21] = 0.0074827005525828338;
		fPoints.PutVal(22, 0, 0.02437018690109383);    fPoints.PutVal(22, 1, 0.86470777029544277);     fWeights[22] = 0.0074827005525828338;
		fPoints.PutVal(23, 0, 0.86470777029544277);    fPoints.PutVal(23, 1, 0.11092204280346339);     fWeights[23] = 0.0074827005525828338;
		fPoints.PutVal(24, 0, 0.11092204280346339);    fPoints.PutVal(24, 1, 0.86470777029544277);     fWeights[24] = 0.0074827005525828338;
		fPoints.PutVal(25, 0, 0.16359740106785048);    fPoints.PutVal(25, 1, 0.087895483032197325);    fWeights[25] = 0.01208951990579691;
		fPoints.PutVal(26, 0, 0.087895483032197325); 	fPoints.PutVal(26, 1, 0.16359740106785048);     fWeights[26] = 0.01208951990579691;
		fPoints.PutVal(27, 0, 0.74850711589995222);    fPoints.PutVal(27, 1, 0.087895483032197325);    fWeights[27] = 0.01208951990579691;
		fPoints.PutVal(28, 0, 0.087895483032197325);   fPoints.PutVal(28, 1, 0.74850711589995222);     fWeights[28] = 0.01208951990579691;
		fPoints.PutVal(29, 0, 0.74850711589995222);    fPoints.PutVal(29, 1, 0.16359740106785048);     fWeights[29] = 0.01208951990579691;
		fPoints.PutVal(30, 0, 0.16359740106785048);    fPoints.PutVal(30, 1, 0.74850711589995222);     fWeights[30] = 0.01208951990579691;
		fPoints.PutVal(31, 0, 0.27251581777342965);    fPoints.PutVal(31, 1, 0.0051263891023823685);   fWeights[31] = 0.0047953405017716316;
		fPoints.PutVal(32, 0, 0.0051263891023823685);  fPoints.PutVal(32, 1, 0.27251581777342965);     fWeights[32] = 0.0047953405017716316;
		fPoints.PutVal(33, 0, 0.72235779312418802);    fPoints.PutVal(33, 1, 0.0051263891023823685);   fWeights[33] = 0.0047953405017716316;
		fPoints.PutVal(34, 0, 0.0051263891023823685);  fPoints.PutVal(34, 1, 0.72235779312418802);     fWeights[34] = 0.0047953405017716316;
		fPoints.PutVal(35, 0, 0.72235779312418802);    fPoints.PutVal(35, 1, 0.27251581777342965);     fWeights[35] = 0.0047953405017716316;
		fPoints.PutVal(36, 0, 0.27251581777342965);    fPoints.PutVal(36, 1, 0.72235779312418802);     fWeights[36] = 0.0047953405017716316;
	}
	
	if (fOrder == 14) {

		fPoints.Resize(46, 2);
		fWeights.resize(46);

		fPoints.PutVal(0, 0, 0.33333333333333331);     fPoints.PutVal(0, 1, 0.33333333333333331);       fWeights[0] = 0.029298142613014298;
		fPoints.PutVal(1, 0, 0.009979760806458432);    fPoints.PutVal(1, 1, 0.98004047838708308);       fWeights[1] = 0.00086757561486263378;
		fPoints.PutVal(2, 0, 0.98004047838708308);      fPoints.PutVal(2, 1, 0.009979760806458432);      fWeights[2] = 0.00086757561486263378;
		fPoints.PutVal(3, 0, 0.009979760806458432);    fPoints.PutVal(3, 1, 0.009979760806458432);      fWeights[3] = 0.00086757561486263378;
		fPoints.PutVal(4, 0, 0.47997789352118841);     fPoints.PutVal(4, 1, 0.040044212957623219);      fWeights[4] = 0.013081891279307261;
		fPoints.PutVal(5, 0, 0.040044212957623219);    fPoints.PutVal(5, 1, 0.47997789352118841);       fWeights[5] = 0.013081891279307261;
		fPoints.PutVal(6, 0, 0.47997789352118841);     fPoints.PutVal(6, 1, 0.47997789352118841);       fWeights[6] = 0.013081891279307261;
		fPoints.PutVal(7, 0, 0.15381195917696691);     fPoints.PutVal(7, 1, 0.69237608164606623);       fWeights[7] = 0.0019598646212009145;
		fPoints.PutVal(8, 0, 0.69237608164606623);     fPoints.PutVal(8, 1, 0.15381195917696691);       fWeights[8] = 0.0019598646212009145;
		fPoints.PutVal(9, 0, 0.15381195917696691);     fPoints.PutVal(9, 1, 0.15381195917696691);       fWeights[9] = 0.0019598646212009145;
		fPoints.PutVal(10, 0, 0.074023477116987813);   fPoints.PutVal(10, 1, 0.85195304576602437);       fWeights[10] = 0.0061236798784704335;
		fPoints.PutVal(11, 0, 0.85195304576602437);    fPoints.PutVal(11, 1, 0.074023477116987813);      fWeights[11] = 0.0061236798784704335;
		fPoints.PutVal(12, 0, 0.074023477116987813);   fPoints.PutVal(12, 1, 0.074023477116987813);      fWeights[12] = 0.0061236798784704335;
		fPoints.PutVal(13, 0, 0.13035468250332999); 	fPoints.PutVal(13, 1, 0.73929063499334002);       fWeights[13] = 0.01409981425162898;
		fPoints.PutVal(14, 0, 0.73929063499334002);    fPoints.PutVal(14, 1, 0.13035468250332999);       fWeights[14] = 0.01409981425162898;
		fPoints.PutVal(15, 0, 0.13035468250332999);    fPoints.PutVal(15, 1, 0.13035468250332999);       fWeights[15] = 0.01409981425162898;
		fPoints.PutVal(16, 0, 0.23061722602665313);    fPoints.PutVal(16, 1, 0.53876554794669373);       fWeights[16] = 0.025443543592979744;
		fPoints.PutVal(17, 0, 0.53876554794669373);    fPoints.PutVal(17, 1, 0.23061722602665313);       fWeights[17] = 0.025443543592979744;
		fPoints.PutVal(18, 0, 0.23061722602665313);    fPoints.PutVal(18, 1, 0.23061722602665313);       fWeights[18] = 0.025443543592979744;
		fPoints.PutVal(19, 0, 0.4223320834191478);     fPoints.PutVal(19, 1, 0.15533583316170435);       fWeights[19] = 0.0252267199508018;
		fPoints.PutVal(20, 0, 0.15533583316170435);    fPoints.PutVal(20, 1, 0.4223320834191478);        fWeights[20] = 0.0252267199508018;
		fPoints.PutVal(21, 0, 0.4223320834191478);     fPoints.PutVal(21, 1, 0.4223320834191478);        fWeights[21] = 0.0252267199508018;
		fPoints.PutVal(22, 0, 0.19061636003190091);    fPoints.PutVal(22, 1, 0.023146254033438094);      fWeights[22] = 0.0085318221061167262;
		fPoints.PutVal(23, 0, 0.023146254033438094);   fPoints.PutVal(23, 1, 0.19061636003190091);       fWeights[23] = 0.0085318221061167262;
		fPoints.PutVal(24, 0, 0.78623738593466097); 	fPoints.PutVal(24, 1, 0.023146254033438094);      fWeights[24] = 0.0085318221061167262;
		fPoints.PutVal(25, 0, 0.023146254033438094);   fPoints.PutVal(25, 1, 0.78623738593466097);       fWeights[25] = 0.0085318221061167262;
		fPoints.PutVal(26, 0, 0.78623738593466097);    fPoints.PutVal(26, 1, 0.19061636003190091);       fWeights[26] = 0.0085318221061167262;
		fPoints.PutVal(27, 0, 0.19061636003190091);    fPoints.PutVal(27, 1, 0.78623738593466097);       fWeights[27] = 0.0085318221061167262;
		fPoints.PutVal(28, 0, 0.36232313774354713);    fPoints.PutVal(28, 1, 0.0071247185958454133);     fWeights[28] = 0.0048417332127533002;
		fPoints.PutVal(29, 0, 0.0071247185958454133);  fPoints.PutVal(29, 1, 0.36232313774354713);       fWeights[29] = 0.0048417332127533002;
		fPoints.PutVal(30, 0, 0.63055214366060741);    fPoints.PutVal(30, 1, 0.0071247185958454133);     fWeights[30] = 0.0048417332127533002;
		fPoints.PutVal(31, 0, 0.0071247185958454133);  fPoints.PutVal(31, 1, 0.63055214366060741);       fWeights[31] = 0.0048417332127533002;
		fPoints.PutVal(32, 0, 0.63055214366060741);    fPoints.PutVal(32, 1, 0.36232313774354713);       fWeights[32] = 0.0048417332127533002;
		fPoints.PutVal(33, 0, 0.36232313774354713);    fPoints.PutVal(33, 1, 0.63055214366060741);       fWeights[33] = 0.0048417332127533002;
		fPoints.PutVal(34, 0, 0.29077120588366739);    fPoints.PutVal(34, 1, 0.082651464260026272);      fWeights[34] = 0.018192877964242501;
		fPoints.PutVal(35, 0, 0.082651464260026272);   fPoints.PutVal(35, 1, 0.29077120588366739);       fWeights[35] = 0.018192877964242501;
		fPoints.PutVal(36, 0, 0.62657732985630632);    fPoints.PutVal(36, 1, 0.082651464260026272);      fWeights[36] = 0.018192877964242501;
		fPoints.PutVal(37, 0, 0.082651464260026272);   fPoints.PutVal(37, 1, 0.62657732985630632);       fWeights[37] = 0.018192877964242501;
		fPoints.PutVal(38, 0, 0.62657732985630632);    fPoints.PutVal(38, 1, 0.29077120588366739);       fWeights[38] = 0.018192877964242501;
		fPoints.PutVal(39, 0, 0.29077120588366739);    fPoints.PutVal(39, 1, 0.62657732985630632);       fWeights[39] = 0.018192877964242501;
		fPoints.PutVal(40, 0, 0.071165710877750768);   fPoints.PutVal(40, 1, 0.014624304192623826);      fWeights[40] = 0.0034823316867592063;
		fPoints.PutVal(41, 0, 0.014624304192623826);   fPoints.PutVal(41, 1, 0.071165710877750768);      fWeights[41] = 0.0034823316867592063;
		fPoints.PutVal(42, 0, 0.91420998492962546);    fPoints.PutVal(42, 1, 0.014624304192623826);      fWeights[42] = 0.0034823316867592063;
		fPoints.PutVal(43, 0, 0.014624304192623826);   fPoints.PutVal(43, 1, 0.91420998492962546);       fWeights[43] = 0.0034823316867592063;
		fPoints.PutVal(44, 0, 0.91420998492962546);    fPoints.PutVal(44, 1, 0.071165710877750768);      fWeights[44] = 0.0034823316867592063;
		fPoints.PutVal(45, 0, 0.071165710877750768);   fPoints.PutVal(45, 1, 0.91420998492962546);       fWeights[45] = 0.0034823316867592063;

	}
	
	if (fOrder == 15) {

		fPoints.Resize(52, 2);
		fWeights.resize(52);

		fPoints.PutVal(0, 0, 0.33333333333333331);     	 fPoints.PutVal(0, 1, 0.33333333333333331);      fWeights[0] = 0.022019355439217139;
		fPoints.PutVal(1, 0, 0.22733221881914287);      	fPoints.PutVal(1, 1, 0.54533556236171421);      fWeights[1] = 0.023092393591013491;
		fPoints.PutVal(2, 0, 0.54533556236171421);      fPoints.PutVal(2, 1, 0.22733221881914287);      fWeights[2] = 0.023092393591013491;
		fPoints.PutVal(3, 0, 0.22733221881914287);      fPoints.PutVal(3, 1, 0.22733221881914287);      fWeights[3] = 0.023092393591013491;
		fPoints.PutVal(4, 0, 0.49716257743188741);      fPoints.PutVal(4, 1, 0.0056748451362251401);      fWeights[4] = 0.0032494533086663583;
		fPoints.PutVal(5, 0, 0.0056748451362251401);      fPoints.PutVal(5, 1, 0.49716257743188741);      fWeights[5] = 0.0032494533086663583;
		fPoints.PutVal(6, 0, 0.49716257743188741);      fPoints.PutVal(6, 1, 0.49716257743188741);      fWeights[6] = 0.0032494533086663583;
		fPoints.PutVal(7, 0, 0.47884973534895459);      fPoints.PutVal(7, 1, 0.042300529302090835);      fWeights[7] = 0.0089968071263292013;
		fPoints.PutVal(8, 0, 0.042300529302090835);      fPoints.PutVal(8, 1, 0.47884973534895459);      fWeights[8] = 0.0089968071263292013;
		fPoints.PutVal(9, 0, 0.47884973534895459);      fPoints.PutVal(9, 1, 0.47884973534895459);      fWeights[9] = 0.0089968071263292013;
		fPoints.PutVal(10, 0, 0.40498603909827197);      fPoints.PutVal(10, 1, 0.19002792180345601);      fWeights[10] = 0.020886552519570677;
		fPoints.PutVal(11, 0, 0.19002792180345601);      fPoints.PutVal(11, 1, 0.40498603909827197);      fWeights[11] = 0.020886552519570677;
		fPoints.PutVal(12, 0, 0.40498603909827197);      fPoints.PutVal(12, 1, 0.40498603909827197);      fWeights[12] = 0.020886552519570677;
		fPoints.PutVal(13, 0, 0.015931216671744432);      fPoints.PutVal(13, 1, 0.96813756665651118);      fWeights[13] = 0.0015297738045582333;
		fPoints.PutVal(14, 0, 0.96813756665651118);      fPoints.PutVal(14, 1, 0.015931216671744432);      fWeights[14] = 0.0015297738045582333;
		fPoints.PutVal(15, 0, 0.015931216671744432);      fPoints.PutVal(15, 1, 0.015931216671744432);      fWeights[15] = 0.0015297738045582333;
		fPoints.PutVal(16, 0, 0.1655832624260814);      fPoints.PutVal(16, 1, 0.6688334751478372);      fWeights[16] = 0.0010062175262793237;
		fPoints.PutVal(17, 0, 0.6688334751478372);      fPoints.PutVal(17, 1, 0.1655832624260814);      fWeights[17] = 0.0010062175262793237;
		fPoints.PutVal(18, 0, 0.1655832624260814);      fPoints.PutVal(18, 1, 0.1655832624260814);      fWeights[18] = 0.0010062175262793237;
		fPoints.PutVal(19, 0, 0.073133604719228723);      fPoints.PutVal(19, 1, 0.8537327905615425);      fWeights[19] = 0.0083878054652545605;
		fPoints.PutVal(20, 0, 0.8537327905615425);      fPoints.PutVal(20, 1, 0.073133604719228723);      fWeights[20] = 0.0083878054652545605;
		fPoints.PutVal(21, 0, 0.073133604719228723);      fPoints.PutVal(21, 1, 0.073133604719228723);      fWeights[21] = 0.0083878054652545605;
		fPoints.PutVal(22, 0, 0.31635283934494723);      fPoints.PutVal(22, 1, 0.01838642758283883);      fWeights[22] = 0.0077303745948571374;
		fPoints.PutVal(23, 0, 0.01838642758283883);      fPoints.PutVal(23, 1, 0.31635283934494723);      fWeights[23] = 0.0077303745948571374;
		fPoints.PutVal(24, 0, 0.66526073307221389);      fPoints.PutVal(24, 1, 0.01838642758283883);      fWeights[24] = 0.0077303745948571374;
		fPoints.PutVal(25, 0, 0.01838642758283883);      fPoints.PutVal(25, 1, 0.66526073307221389);      fWeights[25] = 0.0077303745948571374;
		fPoints.PutVal(26, 0, 0.66526073307221389);      fPoints.PutVal(26, 1, 0.31635283934494723);      fWeights[26] = 0.0077303745948571374;
		fPoints.PutVal(27, 0, 0.31635283934494723);      fPoints.PutVal(27, 1, 0.66526073307221389);      fWeights[27] = 0.0077303745948571374;
		fPoints.PutVal(28, 0, 0.093460751149917531);      fPoints.PutVal(28, 1, 0.19401726160753693);      fWeights[28] = 0.014249945169773712;
		fPoints.PutVal(29, 0, 0.19401726160753693);      fPoints.PutVal(29, 1, 0.093460751149917531);      fWeights[29] = 0.014249945169773712;
		fPoints.PutVal(30, 0, 0.71252198724254556);      fPoints.PutVal(30, 1, 0.19401726160753693);      fWeights[30] = 0.014249945169773712;
		fPoints.PutVal(31, 0, 0.19401726160753693);      fPoints.PutVal(31, 1, 0.71252198724254556);      fWeights[31] = 0.014249945169773712;
		fPoints.PutVal(32, 0, 0.71252198724254556);      fPoints.PutVal(32, 1, 0.093460751149917531);      fWeights[32] = 0.014249945169773712;
		fPoints.PutVal(33, 0, 0.093460751149917531);      fPoints.PutVal(33, 1, 0.71252198724254556);      fWeights[33] = 0.014249945169773712;
		fPoints.PutVal(34, 0, 0.34422901758219321);      fPoints.PutVal(34, 1, 0.096122620182413576);      fWeights[34] = 0.016047175241744798;
		fPoints.PutVal(35, 0, 0.096122620182413576);      fPoints.PutVal(35, 1, 0.34422901758219321);      fWeights[35] = 0.016047175241744798;
		fPoints.PutVal(36, 0, 0.55964836223539327);      fPoints.PutVal(36, 1, 0.096122620182413576);      fWeights[36] = 0.016047175241744798;
		fPoints.PutVal(37, 0, 0.096122620182413576);      fPoints.PutVal(37, 1, 0.55964836223539327);      fWeights[37] = 0.016047175241744798;
		fPoints.PutVal(38, 0, 0.55964836223539327);      fPoints.PutVal(38, 1, 0.34422901758219321);      fWeights[38] = 0.016047175241744798;
		fPoints.PutVal(39, 0, 0.34422901758219321);      fPoints.PutVal(39, 1, 0.55964836223539327);      fWeights[39] = 0.016047175241744798;
		fPoints.PutVal(40, 0, 0.17104724831425794);      fPoints.PutVal(40, 1, 0.018476154066665185);      fWeights[40] = 0.0057542908184353555;
		fPoints.PutVal(41, 0, 0.018476154066665185);      fPoints.PutVal(41, 1, 0.17104724831425794);      fWeights[41] = 0.0057542908184353555;
		fPoints.PutVal(42, 0, 0.81047659761907687);      fPoints.PutVal(42, 1, 0.018476154066665185);      fWeights[42] = 0.0057542908184353555;
		fPoints.PutVal(43, 0, 0.018476154066665185);      fPoints.PutVal(43, 1, 0.81047659761907687);      fWeights[43] = 0.0057542908184353555;
		fPoints.PutVal(44, 0, 0.81047659761907687);      fPoints.PutVal(44, 1, 0.17104724831425794);      fWeights[44] = 0.0057542908184353555;
		fPoints.PutVal(45, 0, 0.17104724831425794);      fPoints.PutVal(45, 1, 0.81047659761907687);      fWeights[45] = 0.0057542908184353555;
		fPoints.PutVal(46, 0, 0.073055996479186494);      fPoints.PutVal(46, 1, 0.010868359489082323);      fWeights[46] = 0.0023071532644835515;
		fPoints.PutVal(47, 0, 0.010868359489082323);      fPoints.PutVal(47, 1, 0.073055996479186494);      fWeights[47] = 0.0023071532644835515;
		fPoints.PutVal(48, 0, 0.91607564403173114);      fPoints.PutVal(48, 1, 0.010868359489082323);      fWeights[48] = 0.0023071532644835515;
		fPoints.PutVal(49, 0, 0.010868359489082323);      fPoints.PutVal(49, 1, 0.91607564403173114);      fWeights[49] = 0.0023071532644835515;
		fPoints.PutVal(50, 0, 0.91607564403173114);      fPoints.PutVal(50, 1, 0.073055996479186494);      fWeights[50] = 0.0023071532644835515;
		fPoints.PutVal(51, 0, 0.073055996479186494);      fPoints.PutVal(51, 1, 0.91607564403173114);      fWeights[51] = 0.0023071532644835515;

	}
	
	if (fOrder == 16) {

		fPoints.Resize(55, 2);
		fWeights.resize(55);

		fPoints.PutVal(0, 0, 0.33333333333333331);     fPoints.PutVal(0, 1, 0.33333333333333331);      fWeights[0] = 0.024011094340188544;
		fPoints.PutVal(1, 0, 0.081794983131373872);    fPoints.PutVal(1, 1, 0.8364100337372522);       fWeights[1] = 0.0073545501534009634;
		fPoints.PutVal(2, 0, 0.8364100337372522);      fPoints.PutVal(2, 1, 0.081794983131373872);     fWeights[2] = 0.0073545501534009634;
		fPoints.PutVal(3, 0, 0.081794983131373872);    fPoints.PutVal(3, 1, 0.081794983131373872);     fWeights[3] = 0.0073545501534009634;
		fPoints.PutVal(4, 0, 0.16530060196977964);     fPoints.PutVal(4, 1, 0.66939879606044073);      fWeights[4] = 0.014772293274659627;
		fPoints.PutVal(5, 0, 0.66939879606044073);     fPoints.PutVal(5, 1, 0.16530060196977964);      fWeights[5] = 0.014772293274659627;
		fPoints.PutVal(6, 0, 0.16530060196977964);     fPoints.PutVal(6, 1, 0.16530060196977964);      fWeights[6] = 0.014772293274659627;
		fPoints.PutVal(7, 0, 0.46859210534946139);     fPoints.PutVal(7, 1, 0.062815789301077229);     fWeights[7] = 0.013062508675544189;
		fPoints.PutVal(8, 0, 0.062815789301077229);    fPoints.PutVal(8, 1, 0.46859210534946139);      fWeights[8] = 0.013062508675544189;
		fPoints.PutVal(9, 0, 0.46859210534946139);     fPoints.PutVal(9, 1, 0.46859210534946139);      fWeights[9] = 0.013062508675544189;
		fPoints.PutVal(10, 0, 0.014438813445416683);   fPoints.PutVal(10, 1, 0.9711223731091666);      fWeights[10] = 0.0013901936761950035;
		fPoints.PutVal(11, 0, 0.9711223731091666);     fPoints.PutVal(11, 1, 0.014438813445416683);    fWeights[11] = 0.0013901936761950035;
		fPoints.PutVal(12, 0, 0.014438813445416683);   fPoints.PutVal(12, 1, 0.014438813445416683);    fWeights[12] = 0.0013901936761950035;
		fPoints.PutVal(13, 0, 0.24178428539178334);    fPoints.PutVal(13, 1, 0.51643142921643326);     fWeights[13] = 0.015910886500268326;
		fPoints.PutVal(14, 0, 0.51643142921643326);    fPoints.PutVal(14, 1, 0.24178428539178334);     fWeights[14] = 0.015910886500268326;
		fPoints.PutVal(15, 0, 0.24178428539178334);    fPoints.PutVal(15, 1, 0.24178428539178334);     fWeights[15] = 0.015910886500268326;
		fPoints.PutVal(16, 0, 0.49531034298776999);    fPoints.PutVal(16, 1, 0.0093793140244600726);   fWeights[16] = 0.0043229171747548303;
		fPoints.PutVal(17, 0, 0.0093793140244600726);  fPoints.PutVal(17, 1, 0.49531034298776999);     fWeights[17] = 0.0043229171747548303;
		fPoints.PutVal(18, 0, 0.49531034298776999);    fPoints.PutVal(18, 1, 0.49531034298776999);     fWeights[18] = 0.0043229171747548303;
		fPoints.PutVal(19, 0, 0.33139974453708954); 	fPoints.PutVal(19, 1, 0.018086852801558143);    fWeights[19] = 0.0071501664522476823;
		fPoints.PutVal(20, 0, 0.018086852801558143); 	fPoints.PutVal(20, 1, 0.33139974453708954);     fWeights[20] = 0.0071501664522476823;
		fPoints.PutVal(21, 0, 0.65051340266135227); 	fPoints.PutVal(21, 1, 0.018086852801558143);    fWeights[21] = 0.0071501664522476823;
		fPoints.PutVal(22, 0, 0.018086852801558143); 	fPoints.PutVal(22, 1, 0.65051340266135227);     fWeights[22] = 0.0071501664522476823;
		fPoints.PutVal(23, 0, 0.65051340266135227); 	fPoints.PutVal(23, 1, 0.33139974453708954);     fWeights[23] = 0.0071501664522476823;
		fPoints.PutVal(24, 0, 0.33139974453708954);    fPoints.PutVal(24, 1, 0.65051340266135227);     fWeights[24] = 0.0071501664522476823;
		fPoints.PutVal(25, 0, 0.30324716274994218); 	fPoints.PutVal(25, 1, 0.092741555754060775);    fWeights[25] = 0.013924888601800415;
		fPoints.PutVal(26, 0, 0.092741555754060775); 	fPoints.PutVal(26, 1, 0.30324716274994218);     fWeights[26] = 0.013924888601800415;
		fPoints.PutVal(27, 0, 0.60401128149599703);    fPoints.PutVal(27, 1, 0.092741555754060775);    fWeights[27] = 0.013924888601800415;
		fPoints.PutVal(28, 0, 0.092741555754060775);   fPoints.PutVal(28, 1, 0.60401128149599703);     fWeights[28] = 0.013924888601800415;
		fPoints.PutVal(29, 0, 0.60401128149599703);    fPoints.PutVal(29, 1, 0.30324716274994218);     fWeights[29] = 0.013924888601800415;
		fPoints.PutVal(30, 0, 0.30324716274994218);    fPoints.PutVal(30, 1, 0.60401128149599703);     fWeights[30] = 0.013924888601800415;
		fPoints.PutVal(31, 0, 0.18802805952123716);    fPoints.PutVal(31, 1, 0.0098036829040211628);   fWeights[31] = 0.0035208367033180486;
		fPoints.PutVal(32, 0, 0.0098036829040211628);  fPoints.PutVal(32, 1, 0.18802805952123716);     fWeights[32] = 0.0035208367033180486;
		fPoints.PutVal(33, 0, 0.80216825757474164);    fPoints.PutVal(33, 1, 0.0098036829040211628);   fWeights[33] = 0.0035208367033180486;
		fPoints.PutVal(34, 0, 0.0098036829040211628);  fPoints.PutVal(34, 1, 0.80216825757474164);     fWeights[34] = 0.0035208367033180486;
		fPoints.PutVal(35, 0, 0.80216825757474164);    fPoints.PutVal(35, 1, 0.18802805952123716);     fWeights[35] = 0.0035208367033180486;
		fPoints.PutVal(36, 0, 0.18802805952123716);    fPoints.PutVal(36, 1, 0.80216825757474164);     fWeights[36] = 0.0035208367033180486;
		fPoints.PutVal(37, 0, 0.18350466852229685);    fPoints.PutVal(37, 1, 0.059989725034874743);    fWeights[37] = 0.0089499191299668643;
		fPoints.PutVal(38, 0, 0.059989725034874743);   fPoints.PutVal(38, 1, 0.18350466852229685);     fWeights[38] = 0.0089499191299668643;
		fPoints.PutVal(39, 0, 0.75650560644282838);    fPoints.PutVal(39, 1, 0.059989725034874743);    fWeights[39] = 0.0089499191299668643;
		fPoints.PutVal(40, 0, 0.059989725034874743);   fPoints.PutVal(40, 1, 0.75650560644282838);     fWeights[40] = 0.0089499191299668643;
		fPoints.PutVal(41, 0, 0.75650560644282838);    fPoints.PutVal(41, 1, 0.18350466852229685);     fWeights[41] = 0.0089499191299668643;
		fPoints.PutVal(42, 0, 0.18350466852229685); 	fPoints.PutVal(42, 1, 0.75650560644282838);     fWeights[42] = 0.0089499191299668643;
		fPoints.PutVal(43, 0, 0.35964594879750461);    fPoints.PutVal(43, 1, 0.17441561248837723);     fWeights[43] = 0.013729100192174881;
		fPoints.PutVal(44, 0, 0.17441561248837723);    fPoints.PutVal(44, 1, 0.35964594879750461);     fWeights[44] = 0.013729100192174881;
		fPoints.PutVal(45, 0, 0.46593843871411816);    fPoints.PutVal(45, 1, 0.17441561248837723);     fWeights[45] = 0.013729100192174881;
		fPoints.PutVal(46, 0, 0.17441561248837723);    fPoints.PutVal(46, 1, 0.46593843871411816);     fWeights[46] = 0.013729100192174881;
		fPoints.PutVal(47, 0, 0.46593843871411816);    fPoints.PutVal(47, 1, 0.35964594879750461);     fWeights[47] = 0.013729100192174881;
		fPoints.PutVal(48, 0, 0.35964594879750461);    fPoints.PutVal(48, 1, 0.46593843871411816);     fWeights[48] = 0.013729100192174881;
		fPoints.PutVal(49, 0, 0.077194371295755432);   fPoints.PutVal(49, 1, 0.016410784712203065);    fWeights[49] = 0.0036498984697158812;
		fPoints.PutVal(50, 0, 0.016410784712203065);   fPoints.PutVal(50, 1, 0.077194371295755432);    fWeights[50] = 0.0036498984697158812;
		fPoints.PutVal(51, 0, 0.90639484399204151);    fPoints.PutVal(51, 1, 0.016410784712203065);    fWeights[51] = 0.0036498984697158812;
		fPoints.PutVal(52, 0, 0.016410784712203065);   fPoints.PutVal(52, 1, 0.90639484399204151);     fWeights[52] = 0.0036498984697158812;
		fPoints.PutVal(53, 0, 0.90639484399204151);    fPoints.PutVal(53, 1, 0.077194371295755432);    fWeights[53] = 0.0036498984697158812;
		fPoints.PutVal(54, 0, 0.077194371295755432);   fPoints.PutVal(54, 1, 0.90639484399204151);     fWeights[54] = 0.0036498984697158812;
	}
	
	if (fOrder == 17) {

		fPoints.Resize(61, 2);
		fWeights.resize(61);

		fPoints.PutVal(0, 0, 0.33333333333333331);     fPoints.PutVal(0, 1, 0.33333333333333331);       fWeights[0] = 0.022378435722172314;
		fPoints.PutVal(1, 0, 0.095698508862710946);    fPoints.PutVal(1, 1, 0.80860298227457816);      fWeights[1] = 0.0086834425133738985;
		fPoints.PutVal(2, 0, 0.80860298227457816);     fPoints.PutVal(2, 1, 0.095698508862710946);     fWeights[2] = 0.0086834425133738985;
		fPoints.PutVal(3, 0, 0.095698508862710946);    fPoints.PutVal(3, 1, 0.095698508862710946);     fWeights[3] = 0.0086834425133738985;
		fPoints.PutVal(4, 0, 0.17013863967877543);     fPoints.PutVal(4, 1, 0.65972272064244908);      fWeights[4] = 0.015299674038051766;
		fPoints.PutVal(5, 0, 0.65972272064244908);     fPoints.PutVal(5, 1, 0.17013863967877543);      fWeights[5] = 0.015299674038051766;
		fPoints.PutVal(6, 0, 0.17013863967877543);     fPoints.PutVal(6, 1, 0.17013863967877543);      fWeights[6] = 0.015299674038051766;
		fPoints.PutVal(7, 0, 0.41802068586795499);     fPoints.PutVal(7, 1, 0.16395862826409005);       fWeights[7] = 0.01429385428929989;
		fPoints.PutVal(8, 0, 0.16395862826409005);     fPoints.PutVal(8, 1, 0.41802068586795499);       fWeights[8] = 0.01429385428929989;
		fPoints.PutVal(9, 0, 0.41802068586795499);     fPoints.PutVal(9, 1, 0.41802068586795499);         fWeights[9] = 0.01429385428929989;
		fPoints.PutVal(10, 0, 0.49658148050662493);    fPoints.PutVal(10, 1, 0.0068370389867500898);     fWeights[10] = 0.0033237159648768465;
		fPoints.PutVal(11, 0, 0.0068370389867500898);  fPoints.PutVal(11, 1, 0.49658148050662493);       fWeights[11] = 0.0033237159648768465;
		fPoints.PutVal(12, 0, 0.49658148050662493);    fPoints.PutVal(12, 1, 0.49658148050662493);       fWeights[12] = 0.0033237159648768465;
		fPoints.PutVal(13, 0, 0.041662114828807641);   fPoints.PutVal(13, 1, 0.91667577034238468);       fWeights[13] = 0.0037380947010092558;
		fPoints.PutVal(14, 0, 0.91667577034238468);    fPoints.PutVal(14, 1, 0.041662114828807641);      fWeights[14] = 0.0037380947010092558;
		fPoints.PutVal(15, 0, 0.041662114828807641);   fPoints.PutVal(15, 1, 0.041662114828807641);      fWeights[15] = 0.0037380947010092558;
		fPoints.PutVal(16, 0, 0.46793290572942359);    fPoints.PutVal(16, 1, 0.06413418854115284);       fWeights[16] = 0.012524993251919372;
		fPoints.PutVal(17, 0, 0.06413418854115284);    fPoints.PutVal(17, 1, 0.46793290572942359);       fWeights[17] = 0.012524993251919372;
		fPoints.PutVal(18, 0, 0.46793290572942359);    fPoints.PutVal(18, 1, 0.46793290572942359);       fWeights[18] = 0.012524993251919372;
		fPoints.PutVal(19, 0, 0.028925091620218245);   fPoints.PutVal(19, 1, 0.0015437094760596976);     fWeights[19] = 0.00073990544605982245;
		fPoints.PutVal(20, 0, 0.0015437094760596976);  fPoints.PutVal(20, 1, 0.028925091620218245);      fWeights[20] = 0.00073990544605982245;
		fPoints.PutVal(21, 0, 0.96953119890372208); 	fPoints.PutVal(21, 1, 0.0015437094760596976);     fWeights[21] = 0.00073990544605982245;
		fPoints.PutVal(22, 0, 0.0015437094760596976);  fPoints.PutVal(22, 1, 0.96953119890372208);       fWeights[22] = 0.00073990544605982245;
		fPoints.PutVal(23, 0, 0.96953119890372208);    fPoints.PutVal(23, 1, 0.028925091620218245);      fWeights[23] = 0.00073990544605982245;
		fPoints.PutVal(24, 0, 0.028925091620218245);   fPoints.PutVal(24, 1, 0.96953119890372208);       fWeights[24] = 0.00073990544605982245;
		fPoints.PutVal(25, 0, 0.23444175526356878);    fPoints.PutVal(25, 1, 0.0058338571978070958);     fWeights[25] = 0.0025605681233740532;
		fPoints.PutVal(26, 0, 0.0058338571978070958);  fPoints.PutVal(26, 1, 0.23444175526356878);       fWeights[26] = 0.0025605681233740532;
		fPoints.PutVal(27, 0, 0.75972438753862415);    fPoints.PutVal(27, 1, 0.0058338571978070958);     fWeights[27] = 0.0025605681233740532;
		fPoints.PutVal(28, 0, 0.0058338571978070958);  fPoints.PutVal(28, 1, 0.75972438753862415);       fWeights[28] = 0.0025605681233740532;
		fPoints.PutVal(29, 0, 0.75972438753862415);    fPoints.PutVal(29, 1, 0.23444175526356878);       fWeights[29] = 0.0025605681233740532;
		fPoints.PutVal(30, 0, 0.23444175526356878);    fPoints.PutVal(30, 1, 0.75972438753862415);       fWeights[30] = 0.0025605681233740532;
		fPoints.PutVal(31, 0, 0.49591124666075359);    fPoints.PutVal(31, 1, 0.20858943637094493);       fWeights[31] = 0.013658679684796404;
		fPoints.PutVal(32, 0, 0.20858943637094493);    fPoints.PutVal(32, 1, 0.49591124666075359);       fWeights[32] = 0.013658679684796404;
		fPoints.PutVal(33, 0, 0.29549931696830151);    fPoints.PutVal(33, 1, 0.20858943637094493);       fWeights[33] = 0.013658679684796404;
		fPoints.PutVal(34, 0, 0.20858943637094493);    fPoints.PutVal(34, 1, 0.29549931696830151);       fWeights[34] = 0.013658679684796404;
		fPoints.PutVal(35, 0, 0.29549931696830151);    fPoints.PutVal(35, 1, 0.49591124666075359);       fWeights[35] = 0.013658679684796404;
		fPoints.PutVal(36, 0, 0.49591124666075359);    fPoints.PutVal(36, 1, 0.29549931696830151);       fWeights[36] = 0.013658679684796404;
		fPoints.PutVal(37, 0, 0.35341769454149707); 	fPoints.PutVal(37, 1, 0.020975923300805905);      fWeights[37] = 0.007002864337954641;
		fPoints.PutVal(38, 0, 0.020975923300805905);   fPoints.PutVal(38, 1, 0.35341769454149707);       fWeights[38] = 0.007002864337954641;
		fPoints.PutVal(39, 0, 0.62560638215769704); 	fPoints.PutVal(39, 1, 0.020975923300805905);      fWeights[39] = 0.007002864337954641;
		fPoints.PutVal(40, 0, 0.020975923300805905); 	fPoints.PutVal(40, 1, 0.62560638215769704);       fWeights[40] = 0.007002864337954641;
		fPoints.PutVal(41, 0, 0.62560638215769704);    fPoints.PutVal(41, 1, 0.35341769454149707);       fWeights[41] = 0.007002864337954641;
		fPoints.PutVal(42, 0, 0.35341769454149707);    fPoints.PutVal(42, 1, 0.62560638215769704);       fWeights[42] = 0.007002864337954641;
		fPoints.PutVal(43, 0, 0.11272864181421977);    fPoints.PutVal(43, 1, 0.015096910952595438);      fWeights[43] = 0.0039046378487291801;
		fPoints.PutVal(44, 0, 0.015096910952595438);   fPoints.PutVal(44, 1, 0.11272864181421977);       fWeights[44] = 0.0039046378487291801;
		fPoints.PutVal(45, 0, 0.87217444723318482); 	fPoints.PutVal(45, 1, 0.015096910952595438);      fWeights[45] = 0.0039046378487291801;
		fPoints.PutVal(46, 0, 0.015096910952595438);   fPoints.PutVal(46, 1, 0.87217444723318482);       fWeights[46] = 0.0039046378487291801;
		fPoints.PutVal(47, 0, 0.87217444723318482);    fPoints.PutVal(47, 1, 0.11272864181421977);       fWeights[47] = 0.0039046378487291801;
		fPoints.PutVal(48, 0, 0.11272864181421977);    fPoints.PutVal(48, 1, 0.87217444723318482);       fWeights[48] = 0.0039046378487291801;
		fPoints.PutVal(49, 0, 0.19907027879785788);    fPoints.PutVal(49, 1, 0.05341740176213608);       fWeights[49] = 0.0090828642298958363;
		fPoints.PutVal(50, 0, 0.05341740176213608);    fPoints.PutVal(50, 1, 0.19907027879785788);       fWeights[50] = 0.0090828642298958363;
		fPoints.PutVal(51, 0, 0.74751231944000607); 	fPoints.PutVal(51, 1, 0.05341740176213608);       fWeights[51] = 0.0090828642298958363;
		fPoints.PutVal(52, 0, 0.05341740176213608);    fPoints.PutVal(52, 1, 0.74751231944000607);       fWeights[52] = 0.0090828642298958363;
		fPoints.PutVal(53, 0, 0.74751231944000607);    fPoints.PutVal(53, 1, 0.19907027879785788);       fWeights[53] = 0.0090828642298958363;
		fPoints.PutVal(54, 0, 0.19907027879785788);    fPoints.PutVal(54, 1, 0.74751231944000607);       fWeights[54] = 0.0090828642298958363;
		fPoints.PutVal(55, 0, 0.30358518307132609);    fPoints.PutVal(55, 1, 0.097546026045435857);      fWeights[55] = 0.013722186996229164;
		fPoints.PutVal(56, 0, 0.097546026045435857);   fPoints.PutVal(56, 1, 0.30358518307132609);       fWeights[56] = 0.013722186996229164;
		fPoints.PutVal(57, 0, 0.59886879088323808);    fPoints.PutVal(57, 1, 0.097546026045435857);      fWeights[57] = 0.013722186996229164;
		fPoints.PutVal(58, 0, 0.097546026045435857);   fPoints.PutVal(58, 1, 0.59886879088323808);       fWeights[58] = 0.013722186996229164;
		fPoints.PutVal(59, 0, 0.59886879088323808);    fPoints.PutVal(59, 1, 0.30358518307132609);       fWeights[59] = 0.013722186996229164;
		fPoints.PutVal(60, 0, 0.30358518307132609);    fPoints.PutVal(60, 1, 0.59886879088323808);       fWeights[60] = 0.013722186996229164;
	}
	
	if (fOrder == 18) {

		fPoints.Resize(72, 2);
		fWeights.resize(72);

		fPoints.PutVal(0, 0, 0.073270886464382831);    fPoints.PutVal(0, 1, 0.85345822707123431);      fWeights[0] = 0.0069889308226430101;
		fPoints.PutVal(1, 0, 0.85345822707123431);     fPoints.PutVal(1, 1, 0.073270886464382831);     fWeights[1] = 0.0069889308226430101;
		fPoints.PutVal(2, 0, 0.073270886464382831);    fPoints.PutVal(2, 1, 0.073270886464382831);     fWeights[2] = 0.0069889308226430101;
		fPoints.PutVal(3, 0, 0.0039177489832282319);   fPoints.PutVal(3, 1, 0.99216450203354356);      fWeights[3] = 0.00027745348960660687;
		fPoints.PutVal(4, 0, 0.99216450203354356);     fPoints.PutVal(4, 1, 0.0039177489832282319);    fWeights[4] = 0.00027745348960660687;
		fPoints.PutVal(5, 0, 0.0039177489832282319);   fPoints.PutVal(5, 1, 0.0039177489832282319);    fWeights[5] = 0.00027745348960660687;
		fPoints.PutVal(6, 0, 0.46759731898871104);     fPoints.PutVal(6, 1, 0.064805362022577875);     fWeights[6] = 0.010513406909852335;
		fPoints.PutVal(7, 0, 0.064805362022577875);    fPoints.PutVal(7, 1, 0.46759731898871104);      fWeights[7] = 0.010513406909852335;
		fPoints.PutVal(8, 0, 0.46759731898871104);      fPoints.PutVal(8, 1, 0.46759731898871104);      fWeights[8] = 0.010513406909852335;
		fPoints.PutVal(9, 0, 0.41791621096741133);      fPoints.PutVal(9, 1, 0.16416757806517737);      fWeights[9] = 0.017009106089963848;
		fPoints.PutVal(10, 0, 0.16416757806517737);    fPoints.PutVal(10, 1, 0.41791621096741133);     fWeights[10] = 0.017009106089963848;
		fPoints.PutVal(11, 0, 0.41791621096741133); 	fPoints.PutVal(11, 1, 0.41791621096741133);     fWeights[11] = 0.017009106089963848;
		fPoints.PutVal(12, 0, 0.56369670566087071);    fPoints.PutVal(12, 1, 0.27092160097883977);     fWeights[12] = 0.013955082902387497;
		fPoints.PutVal(13, 0, 0.27092160097883977);    fPoints.PutVal(13, 1, 0.56369670566087071);     fWeights[13] = 0.013955082902387497;
		fPoints.PutVal(14, 0, 0.16538169336028949);    fPoints.PutVal(14, 1, 0.27092160097883977);     fWeights[14] = 0.013955082902387497;
		fPoints.PutVal(15, 0, 0.27092160097883977);    fPoints.PutVal(15, 1, 0.16538169336028949);     fWeights[15] = 0.013955082902387497;
		fPoints.PutVal(16, 0, 0.16538169336028949);    fPoints.PutVal(16, 1, 0.56369670566087071);     fWeights[16] = 0.013955082902387497;
		fPoints.PutVal(17, 0, 0.56369670566087071);    fPoints.PutVal(17, 1, 0.16538169336028949);     fWeights[17] = 0.013955082902387497;
		fPoints.PutVal(18, 0, 0.28604232613920477);    fPoints.PutVal(18, 1, 0.42645677945501126);     fWeights[18] = 0.0091073430635754335;
		fPoints.PutVal(19, 0, 0.42645677945501126);    fPoints.PutVal(19, 1, 0.28604232613920477);     fWeights[19] = 0.0091073430635754335;
		fPoints.PutVal(20, 0, 0.28750089440578397);    fPoints.PutVal(20, 1, 0.42645677945501126);     fWeights[20] = 0.0091073430635754335;
		fPoints.PutVal(21, 0, 0.42645677945501126);    fPoints.PutVal(21, 1, 0.28750089440578397);     fWeights[21] = 0.0091073430635754335;
		fPoints.PutVal(22, 0, 0.28750089440578397);    fPoints.PutVal(22, 1, 0.28604232613920477);     fWeights[22] = 0.0091073430635754335;
		fPoints.PutVal(23, 0, 0.28604232613920477);    fPoints.PutVal(23, 1, 0.28750089440578397);     fWeights[23] = 0.0091073430635754335;
		fPoints.PutVal(24, 0, 0.69604321864246121);    fPoints.PutVal(24, 1, 0.17806746703771401);     fWeights[24] = 0.0071335118290548963;
		fPoints.PutVal(25, 0, 0.17806746703771401); 	fPoints.PutVal(25, 1, 0.69604321864246121);     fWeights[25] = 0.0071335118290548963;
		fPoints.PutVal(26, 0, 0.12588931431982481);    fPoints.PutVal(26, 1, 0.17806746703771401);     fWeights[26] = 0.0071335118290548963;
		fPoints.PutVal(27, 0, 0.17806746703771401);    fPoints.PutVal(27, 1, 0.12588931431982481);     fWeights[27] = 0.0071335118290548963;
		fPoints.PutVal(28, 0, 0.12588931431982481);    fPoints.PutVal(28, 1, 0.69604321864246121);     fWeights[28] = 0.0071335118290548963;
		fPoints.PutVal(29, 0, 0.69604321864246121);    fPoints.PutVal(29, 1, 0.12588931431982481);     fWeights[29] = 0.0071335118290548963;
		fPoints.PutVal(30, 0, 0.76054555188768247);    fPoints.PutVal(30, 1, 0.17623253216581494);     fWeights[30] = 0.0071185615453375249;
		fPoints.PutVal(31, 0, 0.17623253216581494);    fPoints.PutVal(31, 1, 0.76054555188768247);     fWeights[31] = 0.0071185615453375249;
		fPoints.PutVal(32, 0, 0.063221915946502616);   fPoints.PutVal(32, 1, 0.17623253216581494);     fWeights[32] = 0.0071185615453375249;
		fPoints.PutVal(33, 0, 0.17623253216581494);    fPoints.PutVal(33, 1, 0.063221915946502616);    fWeights[33] = 0.0071185615453375249;
		fPoints.PutVal(34, 0, 0.063221915946502616);   fPoints.PutVal(34, 1, 0.76054555188768247);     fWeights[34] = 0.0071185615453375249;
		fPoints.PutVal(35, 0, 0.76054555188768247);    fPoints.PutVal(35, 1, 0.063221915946502616);    fWeights[35] = 0.0071185615453375249;
		fPoints.PutVal(36, 0, 0.59201963127175861);    fPoints.PutVal(36, 1, 0.32907014127422091);     fWeights[36] = 0.0096287919273373938;
		fPoints.PutVal(37, 0, 0.32907014127422091);    fPoints.PutVal(37, 1, 0.59201963127175861);     fWeights[37] = 0.0096287919273373938;
		fPoints.PutVal(38, 0, 0.078910227454020515); 	fPoints.PutVal(38, 1, 0.32907014127422091);     fWeights[38] = 0.0096287919273373938;
		fPoints.PutVal(39, 0, 0.32907014127422091);    fPoints.PutVal(39, 1, 0.078910227454020515);    fWeights[39] = 0.0096287919273373938;
		fPoints.PutVal(40, 0, 0.078910227454020515);   fPoints.PutVal(40, 1, 0.59201963127175861);     fWeights[40] = 0.0096287919273373938;
		fPoints.PutVal(41, 0, 0.59201963127175861);    fPoints.PutVal(41, 1, 0.078910227454020515);    fWeights[41] = 0.0096287919273373938;
		fPoints.PutVal(42, 0, 0.68368125963599991);    fPoints.PutVal(42, 1, 0.27826068685721445);     fWeights[42] = 0.0048525661421903203;
		fPoints.PutVal(43, 0, 0.27826068685721445); 	fPoints.PutVal(43, 1, 0.68368125963599991);     fWeights[43] = 0.0048525661421903203;
		fPoints.PutVal(44, 0, 0.038058053506785712);   fPoints.PutVal(44, 1, 0.27826068685721445);     fWeights[44] = 0.0048525661421903203;
		fPoints.PutVal(45, 0, 0.27826068685721445);    fPoints.PutVal(45, 1, 0.038058053506785712);    fWeights[45] = 0.0048525661421903203;
		fPoints.PutVal(46, 0, 0.038058053506785712);   fPoints.PutVal(46, 1, 0.68368125963599991);     fWeights[46] = 0.0048525661421903203;
		fPoints.PutVal(47, 0, 0.68368125963599991); 	fPoints.PutVal(47, 1, 0.038058053506785712);    fWeights[47] = 0.0048525661421903203;
		fPoints.PutVal(48, 0, 0.85170403713705578);    fPoints.PutVal(48, 1, 0.13400561073249015);     fWeights[48] = 0.0038148940671660645;
		fPoints.PutVal(49, 0, 0.13400561073249015); 	fPoints.PutVal(49, 1, 0.85170403713705578);     fWeights[49] = 0.0038148940671660645;
		fPoints.PutVal(50, 0, 0.014290352130454025);   fPoints.PutVal(50, 1, 0.13400561073249015);     fWeights[50] = 0.0038148940671660645;
		fPoints.PutVal(51, 0, 0.13400561073249015);    fPoints.PutVal(51, 1, 0.014290352130454025);    fWeights[51] = 0.0038148940671660645;
		fPoints.PutVal(52, 0, 0.014290352130454025);   fPoints.PutVal(52, 1, 0.85170403713705578);     fWeights[52] = 0.0038148940671660645;
		fPoints.PutVal(53, 0, 0.85170403713705578);    fPoints.PutVal(53, 1, 0.014290352130454025);    fWeights[53] = 0.0038148940671660645;
		fPoints.PutVal(54, 0, 0.57473249288814898);    fPoints.PutVal(54, 1, 0.41230023476859778);     fWeights[54] = 0.0053093695681751723;
		fPoints.PutVal(55, 0, 0.41230023476859778);    fPoints.PutVal(55, 1, 0.57473249288814898);     fWeights[55] = 0.0053093695681751723;
		fPoints.PutVal(56, 0, 0.012967272343253173);   fPoints.PutVal(56, 1, 0.41230023476859778);     fWeights[56] = 0.0053093695681751723;
		fPoints.PutVal(57, 0, 0.41230023476859778);    fPoints.PutVal(57, 1, 0.012967272343253173);    fWeights[57] = 0.0053093695681751723;
		fPoints.PutVal(58, 0, 0.012967272343253173);   fPoints.PutVal(58, 1, 0.57473249288814898);     fWeights[58] = 0.0053093695681751723;
		fPoints.PutVal(59, 0, 0.57473249288814898);    fPoints.PutVal(59, 1, 0.012967272343253173);    fWeights[59] = 0.0053093695681751723;
		fPoints.PutVal(60, 0, 0.73551044083072925);    fPoints.PutVal(60, 1, 0.25684096434842979);     fWeights[60] = 0.0028553349016379194;
		fPoints.PutVal(61, 0, 0.25684096434842979);    fPoints.PutVal(61, 1, 0.73551044083072925);     fWeights[61] = 0.0028553349016379194;
		fPoints.PutVal(62, 0, 0.0076485948208408995);  fPoints.PutVal(62, 1, 0.25684096434842979);     fWeights[62] = 0.0028553349016379194;
		fPoints.PutVal(63, 0, 0.25684096434842979);    fPoints.PutVal(63, 1, 0.0076485948208408995);   fWeights[63] = 0.0028553349016379194;
		fPoints.PutVal(64, 0, 0.0076485948208408995);  fPoints.PutVal(64, 1, 0.73551044083072925);     fWeights[64] = 0.0028553349016379194;
		fPoints.PutVal(65, 0, 0.73551044083072925);    fPoints.PutVal(65, 1, 0.0076485948208408995);   fWeights[65] = 0.0028553349016379194;
		fPoints.PutVal(66, 0, 0.93934508764373181);    fPoints.PutVal(66, 1, 0.047944451784012743);    fWeights[66] = 0.0021634287304382093;
		fPoints.PutVal(67, 0, 0.047944451784012743);   fPoints.PutVal(67, 1, 0.93934508764373181);     fWeights[67] = 0.0021634287304382093;
		fPoints.PutVal(68, 0, 0.012710460572255469);   fPoints.PutVal(68, 1, 0.047944451784012743);    fWeights[68] = 0.0021634287304382093;
		fPoints.PutVal(69, 0, 0.047944451784012743);   fPoints.PutVal(69, 1, 0.012710460572255469);    fWeights[69] = 0.0021634287304382093;
		fPoints.PutVal(70, 0, 0.012710460572255469);   fPoints.PutVal(70, 1, 0.93934508764373181);     fWeights[70] = 0.0021634287304382093;
		fPoints.PutVal(71, 0, 0.93934508764373181);    fPoints.PutVal(71, 1, 0.012710460572255469);    fWeights[71] = 0.0021634287304382093;
	}
	
	if (fOrder == 19) {

		fPoints.Resize(73, 2);
		fWeights.resize(73);

		fPoints.PutVal(0, 0, 0.33333333333333331); fPoints.PutVal(0, 1, 0.33333333333333331); fWeights[0] = 0.016453165694459326;
		fPoints.PutVal(1, 0, 0.48960998707300635); fPoints.PutVal(1, 1, 0.020780025853987336); fWeights[1] = 0.0051653659456360268;
		fPoints.PutVal(2, 0, 0.020780025853987336); fPoints.PutVal(2, 1, 0.48960998707300635); fWeights[2] = 0.0051653659456360268;
		fPoints.PutVal(3, 0, 0.48960998707300635); fPoints.PutVal(3, 1, 0.48960998707300635); fWeights[3] = 0.0051653659456360268;
		fPoints.PutVal(4, 0, 0.45453689269789266); fPoints.PutVal(4, 1, 0.09092621460421467); fWeights[4] = 0.011193623631508196;
		fPoints.PutVal(5, 0, 0.09092621460421467); fPoints.PutVal(5, 1, 0.45453689269789266); fWeights[5] = 0.011193623631508196;
		fPoints.PutVal(6, 0, 0.45453689269789266); fPoints.PutVal(6, 1, 0.45453689269789266); fWeights[6] = 0.011193623631508196;
		fPoints.PutVal(7, 0, 0.4014166806494312); fPoints.PutVal(7, 1, 0.19716663870113763); fWeights[7] = 0.015133062934734036;
		fPoints.PutVal(8, 0, 0.19716663870113763); fPoints.PutVal(8, 1, 0.4014166806494312); fWeights[8] = 0.015133062934734036;
		fPoints.PutVal(9, 0, 0.4014166806494312); fPoints.PutVal(9, 1, 0.4014166806494312); fWeights[9] = 0.015133062934734036;
		fPoints.PutVal(10, 0, 0.25555165440309763); fPoints.PutVal(10, 1, 0.4888966911938048); fWeights[10] = 0.015245483901098891;
		fPoints.PutVal(11, 0, 0.4888966911938048); fPoints.PutVal(11, 1, 0.25555165440309763); fWeights[11] = 0.015245483901098891;
		fPoints.PutVal(12, 0, 0.25555165440309763); fPoints.PutVal(12, 1, 0.25555165440309763); fWeights[12] = 0.015245483901098891;
		fPoints.PutVal(13, 0, 0.17707794215212955); fPoints.PutVal(13, 1, 0.64584411569574085); fWeights[13] = 0.012079606370820452;
		fPoints.PutVal(14, 0, 0.64584411569574085); fPoints.PutVal(14, 1, 0.17707794215212955); fWeights[14] = 0.012079606370820452;
		fPoints.PutVal(15, 0, 0.17707794215212955); fPoints.PutVal(15, 1, 0.17707794215212955); fWeights[15] = 0.012079606370820452;
		fPoints.PutVal(16, 0, 0.11006105322795186); fPoints.PutVal(16, 1, 0.77987789354409631); fWeights[16] = 0.0080254017934004371;
		fPoints.PutVal(17, 0, 0.77987789354409631); fPoints.PutVal(17, 1, 0.11006105322795186); fWeights[17] = 0.0080254017934004371;
		fPoints.PutVal(18, 0, 0.11006105322795186); fPoints.PutVal(18, 1, 0.11006105322795186); fWeights[18] = 0.0080254017934004371;
		fPoints.PutVal(19, 0, 0.055528624251839673); fPoints.PutVal(19, 1, 0.88894275149632063); fWeights[19] = 0.0040422901308920303;
		fPoints.PutVal(20, 0, 0.88894275149632063); fPoints.PutVal(20, 1, 0.055528624251839673); fWeights[20] = 0.0040422901308920303;
		fPoints.PutVal(21, 0, 0.055528624251839673); fPoints.PutVal(21, 1, 0.055528624251839673); fWeights[21] = 0.0040422901308920303;
		fPoints.PutVal(22, 0, 0.012621863777228669); fPoints.PutVal(22, 1, 0.97475627244554264); fWeights[22] = 0.0010396810137423905;
		fPoints.PutVal(23, 0, 0.97475627244554264); fPoints.PutVal(23, 1, 0.012621863777228669); fWeights[23] = 0.0010396810137423905;
		fPoints.PutVal(24, 0, 0.012621863777228669); fPoints.PutVal(24, 1, 0.012621863777228669); fWeights[24] = 0.0010396810137423905;
		fPoints.PutVal(25, 0, 0.39575478735694286); fPoints.PutVal(25, 1, 0.0036114178484121379); fWeights[25] = 0.001942438452490695;
		fPoints.PutVal(26, 0, 0.0036114178484121379); fPoints.PutVal(26, 1, 0.39575478735694286); fWeights[26] = 0.001942438452490695;
		fPoints.PutVal(27, 0, 0.60063379479464496); fPoints.PutVal(27, 1, 0.0036114178484121379); fWeights[27] = 0.001942438452490695;
		fPoints.PutVal(28, 0, 0.0036114178484121379); fPoints.PutVal(28, 1, 0.60063379479464496); fWeights[28] = 0.001942438452490695;
		fPoints.PutVal(29, 0, 0.60063379479464496); fPoints.PutVal(29, 1, 0.39575478735694286); fWeights[29] = 0.001942438452490695;
		fPoints.PutVal(30, 0, 0.39575478735694286); fPoints.PutVal(30, 1, 0.60063379479464496); fWeights[30] = 0.001942438452490695;
		fPoints.PutVal(31, 0, 0.55760326158878393); fPoints.PutVal(31, 1, 0.30792998388043624); fWeights[31] = 0.012787080306010952;
		fPoints.PutVal(32, 0, 0.30792998388043624); fPoints.PutVal(32, 1, 0.55760326158878393); fWeights[32] = 0.012787080306010952;
		fPoints.PutVal(33, 0, 0.13446675453077978); fPoints.PutVal(33, 1, 0.30792998388043624); fWeights[33] = 0.012787080306010952;
		fPoints.PutVal(34, 0, 0.30792998388043624); fPoints.PutVal(34, 1, 0.13446675453077978); fWeights[34] = 0.012787080306010952;
		fPoints.PutVal(35, 0, 0.13446675453077978); fPoints.PutVal(35, 1, 0.55760326158878393); fWeights[35] = 0.012787080306010952;
		fPoints.PutVal(36, 0, 0.55760326158878393); fPoints.PutVal(36, 1, 0.13446675453077978); fWeights[36] = 0.012787080306010952;
		fPoints.PutVal(37, 0, 0.26456694840652023); fPoints.PutVal(37, 1, 0.014446025776114736); fWeights[37] = 0.0044404517866690292;
		fPoints.PutVal(38, 0, 0.014446025776114736); fPoints.PutVal(38, 1, 0.26456694840652023); fWeights[38] = 0.0044404517866690292;
		fPoints.PutVal(39, 0, 0.72098702581736507); fPoints.PutVal(39, 1, 0.014446025776114736); fWeights[39] = 0.0044404517866690292;
		fPoints.PutVal(40, 0, 0.014446025776114736); fPoints.PutVal(40, 1, 0.72098702581736507); fWeights[40] = 0.0044404517866690292;
		fPoints.PutVal(41, 0, 0.72098702581736507); fPoints.PutVal(41, 1, 0.26456694840652023); fWeights[41] = 0.0044404517866690292;
		fPoints.PutVal(42, 0, 0.26456694840652023); fPoints.PutVal(42, 1, 0.72098702581736507); fWeights[42] = 0.0044404517866690292;
		fPoints.PutVal(43, 0, 0.35853935220595057); fPoints.PutVal(43, 1, 0.046933578838178489); fWeights[43] = 0.0080622733808656949;
		fPoints.PutVal(44, 0, 0.046933578838178489); fPoints.PutVal(44, 1, 0.35853935220595057); fWeights[44] = 0.0080622733808656949;
		fPoints.PutVal(45, 0, 0.59452706895587093); fPoints.PutVal(45, 1, 0.046933578838178489); fWeights[45] = 0.0080622733808656949;
		fPoints.PutVal(46, 0, 0.046933578838178489); fPoints.PutVal(46, 1, 0.59452706895587093); fWeights[46] = 0.0080622733808656949;
		fPoints.PutVal(47, 0, 0.59452706895587093); fPoints.PutVal(47, 1, 0.35853935220595057); fWeights[47] = 0.0080622733808656949;
		fPoints.PutVal(48, 0, 0.35853935220595057); fPoints.PutVal(48, 1, 0.59452706895587093); fWeights[48] = 0.0080622733808656949;
		fPoints.PutVal(49, 0, 0.15780740596859474); fPoints.PutVal(49, 1, 0.0028611203505666768); fWeights[49] = 0.0012459709087453378;
		fPoints.PutVal(50, 0, 0.0028611203505666768); fPoints.PutVal(50, 1, 0.15780740596859474); fWeights[50] = 0.0012459709087453378;
		fPoints.PutVal(51, 0, 0.8393314736808386); fPoints.PutVal(51, 1, 0.0028611203505666768); fWeights[51] = 0.0012459709087453378;
		fPoints.PutVal(52, 0, 0.0028611203505666768); fPoints.PutVal(52, 1, 0.8393314736808386); fWeights[52] = 0.0012459709087453378;
		fPoints.PutVal(53, 0, 0.8393314736808386); fPoints.PutVal(53, 1, 0.15780740596859474); fWeights[53] = 0.0012459709087453378;
		fPoints.PutVal(54, 0, 0.15780740596859474); fPoints.PutVal(54, 1, 0.8393314736808386); fWeights[54] = 0.0012459709087453378;
		fPoints.PutVal(55, 0, 0.70108797892617336); fPoints.PutVal(55, 1, 0.075050596975910946); fWeights[55] = 0.0091214200594752892;
		fPoints.PutVal(56, 0, 0.075050596975910946); fPoints.PutVal(56, 1, 0.70108797892617336); fWeights[56] = 0.0091214200594752892;
		fPoints.PutVal(57, 0, 0.22386142409791568); fPoints.PutVal(57, 1, 0.075050596975910946); fWeights[57] = 0.0091214200594752892;
		fPoints.PutVal(58, 0, 0.075050596975910946); fPoints.PutVal(58, 1, 0.22386142409791568); fWeights[58] = 0.0091214200594752892;
		fPoints.PutVal(59, 0, 0.22386142409791568); fPoints.PutVal(59, 1, 0.70108797892617336); fWeights[59] = 0.0091214200594752892;
		fPoints.PutVal(60, 0, 0.70108797892617336); fPoints.PutVal(60, 1, 0.22386142409791568); fWeights[60] = 0.0091214200594752892;
		fPoints.PutVal(61, 0, 0.14242160111338345); fPoints.PutVal(61, 1, 0.03464707481675993); fWeights[61] = 0.0051292818680992603;
		fPoints.PutVal(62, 0, 0.03464707481675993); fPoints.PutVal(62, 1, 0.14242160111338345); fWeights[62] = 0.0051292818680992603;
		fPoints.PutVal(63, 0, 0.82293132406985658); fPoints.PutVal(63, 1, 0.03464707481675993); fWeights[63] = 0.0051292818680992603;
		fPoints.PutVal(64, 0, 0.03464707481675993); fPoints.PutVal(64, 1, 0.82293132406985658); fWeights[64] = 0.0051292818680992603;
		fPoints.PutVal(65, 0, 0.82293132406985658); fPoints.PutVal(65, 1, 0.14242160111338345); fWeights[65] = 0.0051292818680992603;
		fPoints.PutVal(66, 0, 0.14242160111338345); fPoints.PutVal(66, 1, 0.82293132406985658); fWeights[66] = 0.0051292818680992603;
		fPoints.PutVal(67, 0, 0.065494628082937698); fPoints.PutVal(67, 1, 0.010161119296278267); fWeights[67] = 0.001899964427650957;
		fPoints.PutVal(68, 0, 0.010161119296278267); fPoints.PutVal(68, 1, 0.065494628082937698); fWeights[68] = 0.001899964427650957;
		fPoints.PutVal(69, 0, 0.92434425262078401); fPoints.PutVal(69, 1, 0.010161119296278267); fWeights[69] = 0.001899964427650957;
		fPoints.PutVal(70, 0, 0.010161119296278267); fPoints.PutVal(70, 1, 0.92434425262078401); fWeights[70] = 0.001899964427650957;
		fPoints.PutVal(71, 0, 0.92434425262078401); fPoints.PutVal(71, 1, 0.065494628082937698); fWeights[71] = 0.001899964427650957;
		fPoints.PutVal(72, 0, 0.065494628082937698); fPoints.PutVal(72, 1, 0.92434425262078401); fWeights[72] = 0.001899964427650957;
	}

	co.resize(2);

	co[0] = fPoints.GetVal(p, 0);
	co[1] = fPoints.GetVal(p, 1);
	weight = fWeights[p];
}