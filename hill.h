#pragma once
#include "Framework.h"

class hill: public Framework
{
public:
	hill(Network * g);
	~hill();
	double get_solution(bool is_ds = true);
	void Inithill(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
	int sumOfMark(vector<vector<int>> Matrix);
    void Resulthill(int s, int t);
    void alg_hill(int n, int s, int t, vector<vector<int>> Matrix);
    void runhill(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
};

