#pragma once
#include "Framework.h"

class bestFS : public Framework
{
public:
    bestFS(Network *g);
    ~bestFS();
    double get_solution(bool is_ds = true);
    void input_BestFS(string filein);
    void best_first_search(int actual, int target, int n);
};