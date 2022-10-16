#pragma once
#include "Framework.h"

class HillClimb: public Framework
{
public:
	HillClimb(Network * g);
	~HillClimb();
	double get_solution(bool is_ds = true);
};

