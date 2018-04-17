//
//  IntRuleQuad.h
//  FemSC
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef __FemSC__IntRuleQuad__
#define __FemSC__IntRuleQuad__

#include <stdio.h>
#include "DataTypes.h"
#include "IntRule.h"

class IntRuleQuad : public IntRule
{
    

public:
  
  IntRuleQuad();
  
  IntRuleQuad(int order);
  
  int NPoints() const;

  void Point(int p, VecDouble &co, double &weight);

  void Print(std::ostream &out) const;
   
  void gaulegQuad(const double x1, const double x2, TMatrix &x, VecDouble &w);

};


#endif /* defined(__FemSC__TIntRule1d__) */
