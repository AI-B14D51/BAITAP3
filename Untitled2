#pragma once
#include "Framework.h"

class BestFS: public Framework
{
public:
	BestFS(Network * g);
	~BestFS();
	double get_solution(bool is_ds = true);
	void InitBestFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
	int sumOfMark(vector<vector<int>> Matrix);
	void alg_BestFS(int n, int u, int t, vector<vector<int>> Matrix);
	void ResultBestFS(int s, int t);
	void runBestFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
	//int trongsomin;
};

