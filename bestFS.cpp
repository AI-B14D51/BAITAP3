#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <queue>
#include "bestFS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

bestFS::bestFS(Network * g) : Framework(g)
{
}

bestFS::~bestFS()
{
}

typedef pair<int, int> pi; 
vector<vector<pi> > GrpBestFS;


void bestFS::AddData(int x, int y, int cost)
{
    GrpBestFS[x].push_back(make_pair(cost, y));
    GrpBestFS[y].push_back(make_pair(cost, x));
}

 void bestFS::Input_BestFS(string filein) {
    GrpBestFS.resize(Constants::n_nodes);
    fstream fin;
    fin.open(filein, ios::in);
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        AddData(u, v, w);
    }
    fin.close();
}

void bestFS::Best_FS_Algorithm(int actual_Src, int target, int n)
{
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duong di: ";
    vector<bool> visited(n, false);
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    pq.push(make_pair(0, actual_Src));
    int s = actual_Src;
    visited[s] = true;
    while (!pq.empty()) {
        int x = pq.top().second;
        fout << x << " => ";
        pq.pop();
        if (x == target)
            break;
 
        for (int i = 0; i < GrpBestFS[x].size(); i++) {
            if (!visited[GrpBestFS[x][i].second]) {
                visited[GrpBestFS[x][i].second] = true;
                pq.push(make_pair(GrpBestFS[x][i].first,GrpBestFS[x][i].second));
            }
        }
    }
    fout.close();
}

double bestFS::get_solution(bool is_ds)
{
    clock_t start = clock();
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "Best First Search\n";
    fout.close();
	Input_BestFS(Constants::FILEIN);
    Best_FS_Algorithm(Constants::start, Constants::end, Constants::n_nodes);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fout.open("output.out", ios::app);
    fout << "\nThoi gian Best First Search: " << time_taken * 1000 << " miliseconds";
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB;\n" << "\tRSS: " << rss << "KB" << endl;
    fout.close();
	return 0.0;
}
