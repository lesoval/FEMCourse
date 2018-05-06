/*
*  GeoNode.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoNode.h"

void GeoNode::Print(std::ostream &out)
{
	out << "POINT COORDINATE = {";
	for (int i = 0; i < xco.size(); i++)
	{
		if (i != 0)
		{
			out << ", ";
		}
		out << xco[i];
	}
	out << "}" << std::endl;
}