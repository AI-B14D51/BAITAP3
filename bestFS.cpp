
#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <queue>
#include "BestFS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

BestFS::BestFS(Network * g) : Framework(g)
{
}

BestFS::~BestFS()
{
}


typedef pair<int, int> pi;
vector<vector<pi> > graph;

//int Pathcost=0;
    // sorting in pq gets done by first value of pair

void BestFS::addedge(int x, int y, int cost)
{
    graph[x].push_back(make_pair(cost, y));
    graph[y].push_back(make_pair(cost, x));
}

void BestFS::InitBestFS(string filein)
{
    graph.resize(Constants::n_nodes);
    fstream fin;
    fin.open(filein, ios::in);
    while (!fin.eof())
    {
        int x, y, cost;
        fin >> x >> y >> cost;
        addedge(x,y,cost);
    }
    fin.close();
}

void BestFS::alg_BestFS(int actual_Src, int target, int n)
{
    fstream fout;
    fout.open("output.out",ios::app);
    vector<bool> visited(n, false);
    // MIN HEAP priority queue
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    // sorting in pq gets done by first value of pair
    pq.push(make_pair(0, actual_Src));
    int s = actual_Src;
    visited[s] = true;
    while (!pq.empty()) {
        int x = pq.top().second;
        // Displaying the path having lowest cost
        fout << x << " ";
        pq.pop();
        if (x == target)
            break;

        for (int i = 0; i < graph[x].size(); i++) {
            if (!visited[graph[x][i].second]) {
                visited[graph[x][i].second] = true;
                pq.push(make_pair(graph[x][i].first,graph[x][i].second));
            }
        }
    }
    fout.close();
}

void BestFS::ResultBestFS(int actual_Src, int target, int n)
{
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "BestFS\n";
    fout << "Duong di ngan nhat tu " << actual_Src << " den " << target << " la" << endl;
    fout.close();
    BestFS::alg_BestFS(actual_Src,target,n);
    fout.open("output.out", ios::app);
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}


void BestFS::runBestFS(string filein,int actual_Src, int target, int n)
{
    // BFS
    clock_t start = clock();
    InitBestFS(filein);
    ResultBestFS(actual_Src, target,n);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time BFS: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double BestFS::get_solution(bool is_ds){
    runBestFS(Constants::FILEIN, Constants::start, Constants::end, Constants::n_nodes);
    return 0.0;
}
