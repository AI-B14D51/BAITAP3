#pragma once
#include "Framework.h"

class IDS: public Framework
{
public:
	IDS(Network * g);
	~IDS();
	double get_solution(bool is_ds = true);
    void Input_IDS(string filein);
    void addEdge(int v, int w);
    int DLS(int v, int g,int l);
    int IDDFS(int v,int g,int l);
    void IDS_exe(string filein, int src, int goal, int limit);
};

