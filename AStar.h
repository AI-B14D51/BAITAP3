#pragma once
#include "Framework.h"

class AStar : public Framework
{
public:
    AStar(Network *g);
    ~AStar();
    double get_solution(bool is_ds = true);
    void input_astar(string filename, string weight);
    void astar_execute(int root,int destination);
    void print_astar(int begin, int destination);
    void run_astar(string filein, string weight, int begin, int destination);

};