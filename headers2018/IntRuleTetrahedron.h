//
//  IntRuleTriangle.h
//  FemSC
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef __FemSC__IntRuleTetrahedron__
#define __FemSC__IntRuleTetrahedron__

#include <stdio.h>
#include "IntRule.h"

class IntRuleTetrahedron : public IntRule
{
      
public:
  
  IntRuleTetrahedron();
  
  IntRuleTetrahedron(int order);
  
  int NPoints() const;

  void Point(int p, VecDouble &co, double &weight);

  void Print(std::ostream &out) const;
};


#endif /* defined(__FemSC__TIntRule1d__) */
