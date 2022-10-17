#pragma once
#include "Framework.h"

class BFS: public Framework
{
public:
	BFS(Network * g);
	~BFS();
	double get_solution(bool is_ds = true);
	void Input_BFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
    void Res_BFS(int s, int t);
    void BFS_Algorithm(int n, int s, int t, vector<vector<int>> Matrix);
    void BFS_exe(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
};

