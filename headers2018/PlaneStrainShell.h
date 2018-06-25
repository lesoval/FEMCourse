/*
*  PlaneStrainShell.h
*
*  Created by Leandro Valdez on 6/24/18.
*
*/

#ifndef PlaneStrainShell_h
#define PlaneStrainShell_h

#include "MathStatement.h"
#include "DataTypes.h"
#include "IntPointData.h"
#include <functional>

class PlaneStrainShell : public MathStatement
{
	//Element thickness
	double t;

	//Constitutive matrix
	Matrix cMat;

	//Force funtion related to ElasticSell math statement
	std::function<void(const VecDouble &co, VecDouble &result)> forceFunction;

public:

	enum PostProcVar { ENone, ESol, EDSol, ETension, EForce, ESolExact, EDSolExact };

	//Default constructor of PlaneStrainShell
	PlaneStrainShell();

	//Constructor of PlaneStrainShell
	PlaneStrainShell(int materialid, double E, double ni, double thickness);

	//Copy constructor of PlaneStrainShell
	PlaneStrainShell(const PlaneStrainShell &copy);

	//Operator of copy
	PlaneStrainShell &operator=(const PlaneStrainShell &copy);

	// Method for creating a copy of the element
	virtual PlaneStrainShell *Clone() const;

	//Destructor of PlaneStrainShell
	virtual ~PlaneStrainShell();

	//Create constitutive matrix
	Matrix Constitutive(double E, double ni);

	// Return the constitutive matrix
	Matrix GetConstitutive() const;

	//Return the force function
	std::function<void(const VecDouble &co, VecDouble &result)> GetForceFunction() const
	{
		return forceFunction;
	}

	//Set the force function
	void SetForceFunction(const std::function<void(const VecDouble &co, VecDouble &result)> &f)
	{
		forceFunction = f;
	}

	virtual int NEvalErrors() const;

	// Return the number of state variables
	virtual int NState() const;

	// returns the integrable dimension of the material
	int Dimension() const { return 2; }

	// Return the variable index associated with the name
	virtual int VariableIndex(const std::string &name);

	// Return the number of variables associated with the variable indexed by var. Param var Index variable into the solution, is obtained by calling VariableIndex
	virtual int NSolutionVariables(const PostProcVar var);

	// Method to implement integral over element's volume
	virtual void Contribute(IntPointData &intpointdata, double weight, Matrix &EK, Matrix &EF) const;

	// Method to implement error over element's volume
	virtual void ContributeError(IntPointData &integrationpointdata, VecDouble &u_exact, Matrix &du_exact, VecDouble &errors) const;

	// Prepare and print post processing data
	virtual std::vector<double> PostProcessSolution(const IntPointData &integrationpointdata, const int var) const;
};
#endif /* PlaneStrainShell_h */
