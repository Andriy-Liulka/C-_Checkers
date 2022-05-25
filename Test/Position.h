
#pragma once



struct Position
{
public:
	int x = 0;
	int y = 0;
	Position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	Position()
	{
	}
	Position(Position& object) :Position(object.x, object.y) {}//sometimes object is equal nullptr

};

