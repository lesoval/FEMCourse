/*
*  TopologyQuad.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "TopologyQuad.h"
#include "tpanic.h"

int TopologyQuad::NSideNodes(int side)
{
	switch (side)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return 1;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		return 2;
		break;
	case 8:
		return 4;
	default:
		std::cout << "TopologyQuad::NSideNodes --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

int TopologyQuad::SideNodeIndex(int side, int node)
{
	switch (side)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return side;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		return (side + node) % 4;
		break;
	case 8:
		return node;
	default:
		std::cout << "TopologyQuad::SideNodeIndex --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

ElementType TopologyQuad::Type()
{
	return EQuadrilateral;
}