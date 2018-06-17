/*
*  Restrain.h
*
*  Created by Leandro Valdez on 6/11/18.
*
*/

#ifndef Restrain_h
#define Restrain_h

#include "MathStatement.h"
#include "DataTypes.h"
#include "IntPointData.h"
#include <functional>

class Restrain : public MathStatement
{

	//Force funtion related to ElasticSell math statement
	std::function<void(const VecDouble &co, VecDouble &result)> forceFunction;

public:

	//Default constructor of Restrain
	Restrain();

	//Constructor of Restrain
	Restrain(int materialid);

	//Copy constructor of Restrain
	Restrain(const Restrain &copy);

	//Operator of copy
	Restrain &operator=(const Restrain &copy);

	// Method for creating a copy of the element
	virtual Restrain *Clone() const;

	//Destructor of Restrain
	virtual ~Restrain();

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

	// Prepare and print post processing data
	virtual std::vector<double> PostProcessSolution(const IntPointData &integrationpointdata, const int var) const;
};
#endif /* Restrain_h */