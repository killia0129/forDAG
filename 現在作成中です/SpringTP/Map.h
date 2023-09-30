#pragma once
#include"game.h"
class Map
{
public:
	Map();
	virtual ~Map();
	void Draw();

private:
	VECTOR pos;
};

