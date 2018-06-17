//
//  IntPointData.h
//  FemCourse
//
//  Created by Philippe Devloo on 24/04/18.
//

#ifndef IntPointData_h
#define IntPointData_h

#include "DataTypes.h"
#include "tpanic.h"

class IntPointData
{
public:

	VecDouble ksi;

	double weight;

	VecDouble phi;

	Matrix dphidksi;

	VecDouble x;

	Matrix gradx;

	Matrix axes;

	double detjac;

	Matrix dphidx;

	VecDouble solution;

	Matrix dsoldksi;

	Matrix dsoldx;

	VecDouble coefs;

	void ComputeSolution()
	{
		if (coefs.size() % phi.size())
		{
			//    DebugStop();
		}
		int nstate = coefs.size() / phi.size();
		solution.resize(nstate);
		for (auto &solval : solution) solval = 0.;
		dsoldksi.Resize(dphidx.Rows(), nstate);
		dsoldx.Resize(dphidx.Rows(), nstate);
		dsoldx.Zero();
		dsoldksi.Zero();
				
		int dim = dphidx.Rows();

		Matrix gradphi(dim, phi.size());

		for (int i = 0; i < phi.size(); i++)
		{
			for (int j = 0; j < dim; j++)
			{
				for (int k = 0; k < dim; k++)
				{
					gradphi(k, i) += dphidx(j, i)*axes(j, k);
				}
			}
		}
				
		for (int iphi = 0; iphi<phi.size(); iphi++) {
			double phival = phi[iphi];
			for (int istate = 0; istate<nstate; istate++) {
				solution[istate] += phival * coefs[iphi*nstate + istate];
				for (int d = 0; d < dim; d++) {
					dsoldksi(d, istate) += coefs[iphi*nstate + istate] * dphidksi(d, iphi);
					dsoldx(d, istate) += coefs[iphi*nstate + istate] * gradphi(d, iphi);
				}
			}
		}
	}
};
#endif /* IntPointData_h */