#pragma once
#include "Framework.h"

class bestFS: public Framework
{
public:
	bestFS(Network * g);
	~bestFS();
	double get_solution(bool is_ds = true);
    void Input_BestFS(string filein);
    void AddData(int x, int y, int cost);
    void Best_FS_Algorithm(int actual_Src, int target, int n);
};
