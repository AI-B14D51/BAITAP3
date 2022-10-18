
#pragma once
#include <queue>
#include "Framework.h"

class BestFS: public Framework
{
public:
	BestFS(Network * g);
	~BestFS();
	double get_solution(bool is_ds = true);
	void addedge(int x,int y, int cost);
	void InitBestFS(string filein);
    void ResultBestFS(int s, int t,int n);
    void alg_BestFS(int s,int t,int n);
    void runBestFS(string filein, int s, int t,int n);
};

