#pragma once
#include "Framework.h"

class Hillclimbing: public Framework
{
public:
	Hillclimbing(Network * g);
	~Hillclimbing();
    void InitHC(string filein, vector<vector<int>> &Matrix);
    void alg_HC(int n, int st, int en, vector<vector<int>> Matrix);
    void resultHC();
	double get_solution(bool is_ds = true);
};
