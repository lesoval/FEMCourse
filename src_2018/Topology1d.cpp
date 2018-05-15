/*
*  Topology1d.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "Topology1d.h"
#include "tpanic.h"

int Topology1d::NSideNodes(int side)
{
	switch (side)
	{
	case 0:
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	default:
		std::cout << "Topology1d::NSideNodes --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

int Topology1d::SideNodeIndex(int side, int node)
{
	switch (side)
	{
	case 0:
	case 1:
		return side;
		break;
	case 2:
		return node;
		break;
	default:
		std::cout << "Topology1d::SideNodeIndex --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

ElementType Topology1d::Type()
{
	return EOned;
}