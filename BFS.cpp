#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include "BFS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

BFS::BFS(Network * g) : Framework(g)
{
}

BFS::~BFS()
{
}

#define MAX 100
#define TRUE 1
#define FALSE 0
#define NUM_MAX_DEFAUL 10000000

vector<int> vet(MAX, 0);   
vector<int> d(MAX, 0);       
vector<int> chuaxet(MAX, 0); 

void BFS::Input_BFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix)
{
    fstream fin;
    fin.open(filein, ios::in);
    Matrix = vector<vector<int>>(MAX, vector<int>(MAX, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Matrix[i][j] = NUM_MAX_DEFAUL;
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        Matrix[u][v] = w;
        Matrix[v][u] = w;
    }
    fin.close();
}

void BFS::Res_BFS(int s, int t)
{
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "BFS\n";
    fout << "Duong di ngan nhat tu " << s << " den " << t << " la" << endl;
    fout << t << "<=";
    int i = vet[t];
    while (i != s)
    {
        fout << i << "<=";
        i = vet[i];
    }
    fout << s;
    fout << endl
         << "Do dai duong di la : " << d[t];
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB;\n" << "\tRSS: " << rss << "KB" << endl;
    fout.close();
}

void BFS::BFS_Algorithm(int n, int s, int t, vector<vector<int>> Matrix)
{
    int u, minp;
    for (int v = 0; v < n; v++)
    {
        d[v] = Matrix[s][v];
        vet[v] = s;
        chuaxet[v] = FALSE;
    }
    vet[s] = 0;
    d[s] = 0;
    chuaxet[s] = TRUE;
    while (!chuaxet[t])
    {
        minp = NUM_MAX_DEFAUL;
        for (int v = 0; v < n; v++)
        {
            if ((!chuaxet[v]) && (minp > d[v]))
            {
                u = v;
                minp = d[v];
            }
        }
        chuaxet[u] = TRUE; 
        if (!chuaxet[t])
        {
            for (int v = 0; v < n; v++)
            {
                if ((!chuaxet[v]) && (d[u] + Matrix[u][v] < d[v]))
                {
                    d[v] = d[u] + Matrix[u][v];
                    vet[v] = u;
                }
            }
        }
    }
}

void BFS::BFS_exe(string filein, int n, int s, int t, vector<vector<int>> &Matrix)
{
    // BFS
    clock_t start = clock();
    Input_BFS(filein, n, s, t, Matrix);
    BFS_Algorithm(n, s, t, Matrix);
    Res_BFS(s, t);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Thoi gian BFS: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double BFS::get_solution(bool is_ds){
    vector<vector<int>> Matrix;
    BFS_exe(Constants::FILEIN, Constants::n_nodes, Constants::start, Constants::end, Matrix);
    return 0.0;
}
