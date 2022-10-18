#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>

#include <vector>
#include <map>
#include <algorithm>
#include "Astar.h"
#include "Constants.h"
#include "memory.h"

using namespace std;

Astar::Astar(Network * g) : Framework(g)
{
}

Astar::~Astar()
{
}

#define MAX 100
#define MAXN 1e6
vector<int> Close;
vector<int> Open;

struct NODE
{
    int g; // ts canh
    int h; // ts dinh
    int f; // g + h
    int pr;
};

map<int, NODE> nodes;
int pathCs = 0;

void InitAstar(string filein, vector<vector<int>> &Matrix)
{
    fstream fin;
    fin.open(filein, ios::in);

    Matrix = vector<vector<int>>(MAX, vector<int>(MAX, 0));

    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        Matrix[u][v] = w;
    }
    fin.close();
    fin.open("nodeWeight.in", ios::in);
    while(!fin.eof()) {
        int u, w;
        fin >> u >> w;
        nodes[u].h = w;
    }
    fin.close();
}


void alg_Astar(int n, int Src, int target, vector<vector<int>> Matrix)
{
    // Khoi tao node[i].f
    for (int i = 0; i < n; i++)
    {
        nodes[i].f = MAXN;
    }

    nodes[Src].g = 0;
    nodes[Src].f = nodes[Src].g + nodes[Src].h;
    Close.push_back(Src);

    while(Src != target)
    {
        for(int i = 0; i < n; i++)
        {
            if(Matrix[Src][i] && find(Close.begin(), Close.end(), i) == Close.end())
            {
                int tmp_g = nodes[Src].g + Matrix[Src][i];
                int tmp_f = tmp_g + nodes[i].h;
                if (tmp_f < nodes[i].f)
                {
                    nodes[i].g = tmp_g;
                    nodes[i].f = tmp_f;
                    nodes[i].pr = Src;
                    if (find(Open.begin(), Open.end(), i) == Open.end())
                    {
                        Open.push_back(i);
                    }
                }
            }
        }

        int ind = 0;
        int Min = nodes[Open[ind]].f;
        for(int i = 1; i < Open.size(); i++)
        {
            if (nodes[Open[i]].f < Min)
            {
                Min = nodes[Open[i]].f;
                ind = i;
            }
        }

        Src = Open[ind];
        Close.push_back(Open[ind]);
        Open.erase(Open.begin() + ind);
    }
}

void result_Astar(int Src, int target, vector<vector<int>> Matrix)
{
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "AStar\n";
    fout << "Duong di tu " << Src << " den " << target << " la: " << endl;
    while(target != Src)
    {
        fout << target << "<-";
        pathCs += Matrix[nodes[target].pr][target];
        target = nodes[target].pr;
    }
    fout << Src;
    fout << "\nTong duong di: " << pathCs;
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

void r_Astar(string filein,int n, int Src,int target)
{
    clock_t start = clock();
    vector<vector<int>> Matrix;
    InitAstar(filein, Matrix);
    alg_Astar(n,Src,target, Matrix);
    result_Astar(Src,target,Matrix);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time Astar: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double Astar::get_solution(bool is_ds)
{
    r_Astar(Constants::FILEIN,Constants::n_nodes,Constants::start,Constants::end);
	return 0.0;
}
