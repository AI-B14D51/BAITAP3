#pragma once
#include "Framework.h"

class IDS: public Framework
{
public:
	IDS(Network * g);
	~IDS();
	double get_solution(bool is_ds = true);
    void InitIDS(string filein, string filein2);
    void addEdge(int v, int w);
    int DLS(int v, int g,int l);
    int IDDFS(int v,int g,int l);
    void runIDS(string filein, string filein2, int src, int goal, int limit);
};

