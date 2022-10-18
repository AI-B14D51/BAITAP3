#pragma once
#include "Framework.h"

class BFS : public Framework
{
public:
	BFS(Network *g);
	~BFS();
	double get_solution(bool is_ds = true);
	void input_bfs(string filein);
	void print_bfs(int begin, int destination);
	void bfs_execute(int root, int n);
	void run_bfs(string filein, int begin, int destination);
};
