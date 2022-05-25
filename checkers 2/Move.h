#include "Position.h"
#pragma once


struct Move
{
public:
	Position* from = nullptr;
	Position* to = nullptr;

	Move(Position* from, Position* to)
	{
		this->from = from;
		this->to = to;
	}
	Move() {}
		

};