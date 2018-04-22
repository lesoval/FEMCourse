//
//  Shape1d.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef Shape1d_h
#define Shape1d_h

#include "DataTypes.h"

class Shape1d
{
public:
    // Computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
    static void Shape(VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi);
    
    // Returns the number of shape functions associated with a side
    static int NShapeFunctions(int side, VecInt &orders);
    
    // Returns the total number of shape functions
    static int NShapeFunctions(VecInt &orders);

};

#endif /* Shape1d_h */
