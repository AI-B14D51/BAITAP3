#pragma once
#include "Framework.h"

class Astar:public Framework
{
    public:
    Astar(Network(*g));
    ~Astar();
    double get_solution(bool is_ds = true);
	void InitAstar(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
	void alg_Astar(int n, int u, int t, vector<vector<int>> Matrix);
	void runAstar(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
};
