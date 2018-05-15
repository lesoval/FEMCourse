/*
*  TopologyTetrahedron.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "TopologyTetrahedron.h"
#include "tpanic.h"

int TopologyTetrahedron::NSideNodes(int side)
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
	case 8:
	case 9:
		return 2;
			break;
	case 10:
	case 11:
	case 12:
	case 13:
		return 3;
			break;
	case 14:
		return 4;
			break;
	default:
		std::cout << "TopologyTetrahedron::NSideNodes --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

int TopologyTetrahedron::SideNodeIndex(int side, int node)
{
	int SideNodes[6][2] = { { 0,1 },{ 1,2 },{ 2,0 },{ 0,3 },{ 1,3 },{ 2,3 } };
	int FaceNodes[4][3] = { { 0,1,2 },{ 0,1,3 },{ 1,2,3 },{ 0,2,3 } };

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
	case 8:
	case 9:
		return SideNodes[side - 4][node];
		break;
	case 10:
	case 11:
	case 12:
	case 13:
		return FaceNodes[side - 10][node];
		break;
	case 14:
		return node;
		break;
	default:
		std::cout << "TopologyTetrahedron::SideNodeIndex --> Invalid argument 'side' " << side << std::endl;
		DebugStop();
		break;
	}
}

ElementType TopologyTetrahedron::Type()
{
	return ETetraedro;
}