#pragma once
#include "Framework.h"

class Astar: public Framework
{
public:
	Astar(Network * g);
	~Astar();
	double get_solution(bool is_ds = true);
};
