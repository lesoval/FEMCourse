//
//  IntRule.h
//  FemSC
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef __FemSC__IntRule__
#define __FemSC__IntRule__

#include <cmath>
#include <stdio.h>
#include "DataTypes.h"

class IntRule
{
  
protected:
    
    int fOrder;

    Matrix fPoints;
    
    VecDouble fWeights;

public:
  
    //Default Constructor of integration rule
    IntRule();
    
    IntRule(int order);
    
    ~IntRule();

	void SetOrder(int order);
   
    void operator=(const IntRule &copy);
    
    IntRule(const IntRule &copy);
		        
    virtual int NPoints() const;
    
    virtual void Point(int p, VecDouble &co, double &weight);
    
    virtual void Print(std::ostream &out) const;
    
};


#endif /* defined(__FemSC__TIntRule1d__) */
