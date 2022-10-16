#pragma once
#include "Framework.h"

class DFS: public Framework
{
public:
	DFS(Network * g);
	~DFS();
	double get_solution(bool is_ds = true);
	void InitDFS(string filein, string filein2, int n, int s, int t, vector<vector<int>> &Matrix);
	int sumOfMark(vector<vector<int>> Matrix);
	void alg_DFS(int n, int u, int t, vector<vector<int>> Matrix);
	void ResultDFS(int s, int t);
	void runDFS(string filein, string filein2, int n, int s, int t, vector<vector<int>> &Matrix);
};

