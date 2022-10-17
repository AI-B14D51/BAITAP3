#pragma once
#include "Framework.h"

class hillClimbing: public Framework
{
public:
	hillClimbing(Network * g);
	~hillClimbing();
	double get_solution(bool is_ds = true);
};

