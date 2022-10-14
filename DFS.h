#pragma once
#include "Framework.h"

class DFS : public Framework
{
public:
	DFS(Network *g);
	~DFS();
	double get_solution(bool is_ds = true);
	void input_dfs(string filein);
	int sum_of_mark(int destination);
	void dfs_execute(int vt, int destination);
	void print_result(int destination);
	void run_dfs(string filein, int begin, int destination);
};
