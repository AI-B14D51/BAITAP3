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
vector<int> Close;
vector<int> Open;

struct NODE {
    int g; // ts canh
    int h; // ts dinh
    int f; // g + h
    int cha;
};

map<int, NODE> nodes;

void InitAstar(string filein, string filein2, vector<vector<int>> &Matrix) {
    Matrix = vector<vector<int>>(MAX, vector<int>(MAX, 0));
    fstream fin,fin2;
    fin.open(filein, ios::in);
    while (!fin.eof())
    {
        int x, y, z;
        fin >> x >> y >> z;
        Matrix[x][y] = z;
    }
    fin.close();
    fin2.open(filein2, ios::in);
    while(!fin2.eof()) {
        int x, z;
        fin2 >> x >> z;
        nodes[x].h = z;
    }
    fin2.close();
}

void Xuly_Astar(int n, int s, int t, vector<vector<int>> Matrix) {
    // gan gia tri dau cho node[i].f
    for (int i = 0; i < n; i++) {
        nodes[i].f = 1e6;
    }

    nodes[s].g = 0;
    nodes[s].f = nodes[s].g + nodes[s].h;
    Close.push_back(s);

    while(s != t) {
        for(int i = 0; i < n; i++) {
            if(Matrix[s][i] && find(Close.begin(), Close.end(), i) == Close.end()) {
                int tg_g = nodes[s].g + Matrix[s][i];
                int tg_f = tg_g + nodes[i].h;
                if (tg_f < nodes[i].f) {
                    nodes[i].g = tg_g;
                    nodes[i].f = tg_f;
                    nodes[i].cha = s;                   
                    if (find(Open.begin(), Open.end(), i) == Open.end()) {
                        Open.push_back(i);
                    }
                }
            }
        }

        int ind = 0;
        int Min = nodes[Open[ind]].f;
        for(int i = 1; i < Open.size(); i++) {
            if (nodes[Open[i]].f < Min) {
                Min = nodes[Open[i]].f;
                ind = i;
            }
        }

        s = Open[ind];
        Close.push_back(Open[ind]);
        Open.erase(Open.begin() + ind);
    }
}

void Result_Astar(int s, int t, vector<vector<int>> Matrix) {
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "Astar\n";
    fout << "Duong di tu " << s << " den " << t << " la: " << endl;
    int cost =nodes[t].h;
    while(t != s) {
        fout << t << "<-";
        int a = nodes[t].cha;
        cost=cost+nodes[a].h+Matrix[t][a];
        t=a;
    }
    cost=cost+nodes[s].h;
    fout << s<<endl;
    fout << "Do dai duong di la: "<<cost<<endl;
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "Memory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

double Astar::get_solution(bool is_ds)
{
    clock_t start = clock();
    vector<vector<int>> Matrix;
    InitAstar(Constants::FILEIN, Constants::FILEIN2, Matrix);
    Xuly_Astar(Constants::n_nodes, Constants::start, Constants::end, Matrix);
    Result_Astar(Constants::start, Constants::end, Matrix);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time Astar: " << time_taken * 1000 << " miliseconds";
    fout.close();
	return 0.0;
}
