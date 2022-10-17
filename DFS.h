#pragma once
#include "Framework.h"

class DFS: public Framework
{
public:
	DFS(Network * g);
	~DFS();
	double get_solution(bool is_ds = true);
	void Input_DFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
	int Sum_Of_Mark(vector<vector<int>> Matrix);
	void DFS_Algorithm(int n, int u, int t, vector<vector<int>> Matrix);
	void Res_DFS(int s, int t);
	void BFS_exe(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
};

