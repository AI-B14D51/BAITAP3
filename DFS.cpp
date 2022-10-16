#include <iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include "DFS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

DFS::DFS(Network *g) : Framework(g)
{
}

DFS::~DFS()
{
}

#define max 100
int length_road = INT32_MAX;
vector<int> graph[max];
vector<int> mark;
vector<int> result;
bool visited[max];
int matrixDFS[max][max];

void DFS::input_dfs(string filein)
{
    fstream fin;
    fin.open(filein, ios::in);
    while (!fin.eof())
    {
        int x, y, z;
        fin >> x >> y >> z;
        graph[x].push_back(y);
        graph[y].push_back(x);
        matrixDFS[x][y] = z;
        matrixDFS[y][x] = z;
    }
    fin.close();
}

int DFS::sum_of_mark(int destination)
{
    int res = 0;
    for (int i = 0; i < (int)mark.size() - 1; i++)
    {
        res += matrixDFS[mark[i]][mark[i + 1]];
    }
    return res + matrixDFS[mark[mark.size() - 1]][destination];
}

void DFS::dfs_execute(int vt, int destination)
{
    for (int i = 0; i < graph[vt].size(); i++)
    {
        int v = graph[vt][i];
        if (!visited[v])
        {
            visited[v] = true;
            if (v == destination)
            {
                int distance = sum_of_mark(destination);
                if (length_road > distance)
                {
                    length_road = distance;
                    result = mark;
                }
                visited[v] = false;
            }
            else
            {
                mark.push_back(v);
                dfs_execute(v,destination);
                visited[v] = false;
                mark.pop_back();
            }
        }
    }
}

void DFS::print_result(int destination)
{
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "DFS" << endl;
    fout << "Path : " << endl;
    for (int i = 0; i < result.size(); i++)
        fout << result[i] << " => ";
    fout << destination << endl;
    fout << "Length : " << length_road << endl;
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "Memory: "
         << "VM: " << vm << " KB"
         << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

void DFS::run_dfs(string filein, int begin, int destination)
{
    clock_t start = clock();
    input_dfs(filein);
    mark.push_back(begin);
    visited[begin] = true;
    dfs_execute(begin, destination);
    print_result(destination);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "Time taken by dfs is: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double DFS::get_solution(bool is_ds)
{
    run_dfs(Constants::FILEIN, Constants::start, Constants::end);
    return 0.0;
}
