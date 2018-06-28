/*
*  PlaneStressShell.h
*
*  Created by Leandro Valdez on 6/11/18.
*
*/

#ifndef PlaneStressShell_h
#define PlaneStressShell_h

#include "MathStatement.h"
#include "DataTypes.h"
#include "IntPointData.h"
#include <functional>

class PlaneStressShell : public MathStatement
{
	//Element thickness
	double t;

	//Constitutive matrix
	Matrix cMat;

	//Force funtion related to ElasticSell math statement
	std::function<void(const VecDouble &co, VecDouble &result)> forceFunction;

	std::function<void(const VecDouble &loc, VecDouble &result, Matrix &deriv)> SolutionExact;

public:

	enum PostProcVar { ENone, ESol, EDSol, EFlux, EForce, ESolExact, EDSolExact };

	//Default constructor of PlaneStressShell
	PlaneStressShell();

	//Constructor of PlaneStressShell
	PlaneStressShell(int materialid, double E, double ni, double thickness);

	//Copy constructor of PlaneStressShell
	PlaneStressShell(const PlaneStressShell &copy);

	//Operator of copy
	PlaneStressShell &operator=(const PlaneStressShell &copy);

	//Destructor of PlaneStressShell
	virtual ~PlaneStressShell();

	// Method for creating a copy of the element
	virtual PlaneStressShell *Clone() const;

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

	// Set the exact solution related to Plane Stress math statement
	void SetExactSolution(const std::function<void(const VecDouble &loc, VecDouble &result, Matrix &deriv)> &Exact)
	{
		SolutionExact = Exact;
	}

	virtual int NEvalErrors() const;

	// Return the number of state variables
	virtual int NState() const;

	virtual int VariableIndex(const PostProcVar var) const;

	// Return the variable index associated with the name
	virtual PostProcVar VariableIndex(const std::string &name);

	// Return the number of variables associated with the variable indexed by var. Param var Index variable into the solution, is obtained by calling VariableIndex
	virtual int NSolutionVariables(const PostProcVar var);

	// Method to implement integral over element's volume
	virtual void Contribute(IntPointData &intpointdata, double weight, Matrix &EK, Matrix &EF) const;

	// Method to implement error over element's volume
	virtual void ContributeError(IntPointData &integrationpointdata, VecDouble &u_exact, Matrix &du_exact, VecDouble &errors) const;

	// Prepare and print post processing data
	virtual void PostProcessSolution(const IntPointData &integrationpointdata, const int var, VecDouble &sol) const;
};
#endif /* PlaneStressShell_h */
