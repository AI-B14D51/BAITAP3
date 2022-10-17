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
vector<int> closed;
vector<int> open;

struct NODE {
    int g; // ts canh
    int h; // ts dinh
    int f; // g + h
    int cha;
};

map<int, NODE> nodes;

void InitAstar(string filein, vector<vector<int>> &Matrix) {
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


void alg_Astar(int n, int st, int en, vector<vector<int>> Matrix) {
    // gan gia tri dau cho node[i].f
    for (int i = 0; i < n; i++) {
        nodes[i].f = 1e6;
    }

    nodes[st].g = 0;
    nodes[st].f = nodes[st].g + nodes[st].h;
    closed.push_back(st);

    while(st != en) {
        for(int i = 0; i < n; i++) {
            if(Matrix[st][i] && find(closed.begin(), closed.end(), i) == closed.end()) {
                int tg_g = nodes[st].g + Matrix[st][i];
                int tg_f = tg_g + nodes[i].h;
                if (tg_f < nodes[i].f) {
                    nodes[i].g = tg_g;
                    nodes[i].f = tg_f;
                    nodes[i].cha = st;                   
                    if (find(open.begin(), open.end(), i) == open.end()) {
                        open.push_back(i);
                    }
                }
            }
        }

        int ind = 0;
        int Min = nodes[open[ind]].f;
        for(int i = 1; i < open.size(); i++) {
            if (nodes[open[i]].f < Min) {
                Min = nodes[open[i]].f;
                ind = i;
            }
        }

        st = open[ind];
        closed.push_back(open[ind]);
        open.erase(open.begin() + ind);
    }
}

void result_Astar(int st, int en, vector<vector<int>> Matrix) {
    int sum = 0;
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "Astar\n";
    fout << "Duong di tu " << st << " den " << en << " la: " << endl;
    while(en != st) {
        fout << en << "<-";
        sum += Matrix[nodes[en].cha][en];
        en = nodes[en].cha;
    }
    fout << st;
    fout << "\nTong duong di: " << sum;
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

double Astar::get_solution(bool is_ds)
{
    clock_t start = clock();
    vector<vector<int>> Matrix;
    InitAstar(Constants::FILEIN, Matrix);
    alg_Astar(Constants::n_nodes, Constants::start, Constants::end, Matrix);
    result_Astar(Constants::start, Constants::end, Matrix);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time Astar: " << time_taken * 1000 << " miliseconds";
    fout.close();
	return 0.0;
}
