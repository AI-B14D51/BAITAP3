#include <iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <utility>
#include <queue>

#include "AStar.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

AStar::AStar(Network *g) : Framework(g)
{
}

AStar::~AStar()
{
}
#define max 100
#define maxr 10000000
typedef pair<int,int> ii;
vector<ii> graph[max];
int matrix[max][max];
int check[max];
int d[max];
int weight[max];

void AStar::input_astar(string filename, string weight){
    fstream fin;
    fin.open(filename,ios::in);
    while(!fin.eof()){
        int x,y,z;
        fin >> x >> y >> z;
        graph[x].push_back(make_pair(y, z));
        graph[y].push_back(make_pair(x, z));
    }
    fin.close();
    fin.open(weight,ios::in);
    while(!fin.eof()){
        int x,y;
        fin >> x >> y;
        weight[x] = y;
    }

}

void AStar::astar_execute(int root, int destination){
    priority_queue<ii, vector<ii>, greater<ii>> road;
    for (int i = 0; i < max; i++)
    {
        d[i] = maxr;
    }
    d[root] = 0;
    road.push(ii(root, 0));
    while (!road.empty())
    {
        ii top = road.top();
        road.pop();
        int u = top.first;
        if (d[u] != top.second)
            continue;

        for (int i = 0; i < graph[u].size(); i++)
        {
            int v = graph[u][i].first;
            int uv = graph[u][i].second;
            if (d[v] + weight[v] > d[u] + uv + weight[v])
            {
                d[v] = d[u] + uv;
                road.push(ii(v, d[v]));
                check[v] = u;
                if(v == destination) break;
            }
        }
    }
}

void AStar::print_astar(int begin, int destination)
{
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "A Star\n";
    fout << "Path : " << endl;
    fout << destination << " <= ";
    int i = check[destination];
    while (i != begin)
    {
        fout << i << " <= ";
        i = check[i];
    }
    fout << begin;
    fout << endl
         << "Length : " << d[destination] << endl;
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: "
         << "VM: " << vm << " KB"
         << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

void AStar::run_astar(string filein, string weight, int begin, int destination)
{

    clock_t start = clock();
    input_astar(filein, weight);
    astar_execute(begin, destination);
    print_astar(begin, destination);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Time taken by a star: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double AStar::get_solution(bool is_ds)
{
    run_astar(Constants::FILEIN,Constants::WEIGHT, Constants::start, Constants::end);
    return 0.0;
}