//
//  IntRuleTriangle.h
//  FemSC
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef __FemSC__IntRuleTriangle__
#define __FemSC__IntRuleTriangle__

#include <stdio.h>
#include "IntRule.h"

class IntRuleTriangle : public IntRule
{
  
public:
  
  IntRuleTriangle();
  
  IntRuleTriangle(int order);
  
  int NPoints() const;

  void Point(int p, VecDouble &co, double &weight);

  void Print(std::ostream &out) const;  
};


#endif /* defined(__FemSC__TIntRule1d__) */
