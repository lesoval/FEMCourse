/*
*  MathStatement.cpp
*
*  Created by Leandro Valdez on 5/5/18.
*
*/

#include "MathStatement.h"

MathStatement::MathStatement() {}

MathStatement::MathStatement(const MathStatement &copy)
{
	this->operator=(copy);
}

MathStatement &MathStatement::operator=(const MathStatement &copy)
{
	matid = copy.matid;
	nstate = copy.nstate;

	return *this;
}

MathStatement::~MathStatement() {}
