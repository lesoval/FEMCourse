//
//  IntRule1d.h
//  FemSC
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef __FemSC__IntRule1d__
#define __FemSC__IntRule1d__

#include <cmath>
#include <stdio.h>
#include "IntRule.h"

class IntRule1d : public IntRule
{
    
public:
  
    IntRule1d();
    
    IntRule1d(int order);

	int NPoints() const;

	void Point(int p, VecDouble &co, double &weight);

	void Print(std::ostream &out) const;
        
    void gauleg(const double x1, const double x2, TMatrix &x, VecDouble &w);
    
};


#endif /* defined(__FemSC__TIntRule1d__) */
