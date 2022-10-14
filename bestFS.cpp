#include <iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <queue>
#include "bestFS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

bestFS::bestFS(Network *g) : Framework(g)
{
}

bestFS::~bestFS()
{
}

typedef pair<int, int> ii;
vector<vector<ii>> graphBest;

void bestFS::input_BestFS(string filein)
{
    fstream fin;
    fin.open(filein, ios::in);
    while (!fin.eof())
    {
        int x, y, z;
        fin >> x >> y >> z;
        graphBest[x].push_back(make_pair(y,z));
        graphBest[y].push_back(make_pair(x,z));
    }
    fin.close();
}

void bestFS::best_first_search(int actual, int target, int n)
{
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "Path: ";
    vector<bool> visited(n, false);

    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(make_pair(0, actual));
    int s = actual;
    visited[s] = true;
    while (!pq.empty())
    {
        int x = pq.top().second;

        fout << x << " ";
        pq.pop();
        if (x == target)
            break;

        for (int i = 0; i < graphBest[x].size(); i++)
        {
            if (!visited[graphBest[x][i].second])
            {
                visited[graphBest[x][i].second] = true;
                pq.push(make_pair(graphBest[x][i].first, graphBest[x][i].second));
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
    fout << "Best First Search" << endl;
    fout.close();
    input_BestFS(Constants::FILEIN);
    best_first_search(Constants::start, Constants::end, Constants::n_nodes);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "Time taken by best first search is: " << time_taken * 1000 << " miliseconds" << endl;
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "Memory: "
         << "VM: " << vm << " KB"
         << "; RSS: " << rss << "KB" << endl;
    fout.close();
    return 0.0;
}
