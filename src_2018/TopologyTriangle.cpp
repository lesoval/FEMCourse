/*
*  TopologyTriangle.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "TopologyTriangle.h"
#include "tpanic.h"

static int NSideNodes(int side)
{
	switch (side)
	{
	case 0:
	case 1:
	case 2:
		return 1;
		break;
	case 3:
	case 4:
	case 5:
		return 2;
		break;
	case 6:
		return 3;
		break;
	default:
		std::cout << "TopologyTriangle::NSideNodes --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

static int SideNodeIndex(int side, int node)
{
	if (node<NSideNodes(side) - 1 || node>NSideNodes(side) - 1)
	{
		std::cout << "TopologyTriangle::SideNodeIndex --> Node invalid for 'side' " << side << std::endl;
		DebugStop();
	}

	switch (side)
	{
	case 0:
	case 1:
	case 2:
		return side;
		break;
	case 3:
	case 4:
	case 5:
		return (side - 3 + node) % 3;
		break;
	case 6:
		return node;
		break;
	default:
		std::cout << "TopologyTriangle::SideNodeIndex --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

ElementType TopologyTriangle::Type()
{
	return ETriangle;
}