/*
*  OnlyForce.h
*
*  Created by Leandro Valdez on 6/11/18.
*
*/

#ifndef OnlyForce_h
#define OnlyForce_h

#include "MathStatement.h"
#include "DataTypes.h"
#include "IntPointData.h"
#include <functional>

class OnlyForce : public MathStatement
{

	//Force funtion related to ElasticSell math statement
	std::function<void(const VecDouble &co, VecDouble &result)> forceFunction;

public:

	//Default constructor of OnlyForce
	OnlyForce();

	//Constructor of OnlyForce
	OnlyForce(int materialid);

	//Copy constructor of OnlyForce
	OnlyForce(const OnlyForce &copy);

	//Operator of copy
	OnlyForce &operator=(const OnlyForce &copy);

	// Method for creating a copy of the element
	virtual OnlyForce *Clone() const;

	//Destructor of OnlyForce
	virtual ~OnlyForce();

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

	// Method to implement integral over element's volume
	virtual void Contribute(IntPointData &intpointdata, double weight, Matrix &EK, Matrix &EF) const;

	// Method to implement error over element's volume
	virtual void ContributeError(IntPointData &integrationpointdata, VecDouble &u_exact, Matrix &du_exact, VecDouble &errors) const;
};
#endif /* OnlyForce_h */

