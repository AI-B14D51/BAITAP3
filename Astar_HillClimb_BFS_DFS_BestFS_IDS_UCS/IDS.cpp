#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <map>
#include "IDS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

#define MAX 100
map<int, vector<int>> adj;

IDS::IDS(Network * g) : Framework(g)
{
}

IDS::~IDS()
{
}

void IDS::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void IDS::InitIDS(string filein, string filein2)
{
    fstream fin,fin2;
    fin2.open(filein2, ios::in);
    int u, v, w, a, b;
    
    while (!fin2.eof())
    {
    	fin2 >>a >>b;
    	fin.open(filein, ios::in);
      while (!fin.eof())
    {
        fin >> u >> v >> w;
        if(a==u){
        	w=w+b;
        	addEdge(u, v);
		}
	}
		fin.close();  
	}
	fin2.close();
}

int IDS::DLS(int v, int goal, int limit)
{   

    if (v == goal)
    {
        return 1;
    }
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (limit - 1 >= 0)
        {
            fstream fout;
            fout.open("output.out", ios::app);
            fout << *i << " ";
            fout.close();
            if (DLS(*i, goal, limit - 1) != -1)
                return 1;
        }
    }
    return -1;
}

int IDS::IDDFS(int src, int goal, int limit)
{
    fstream fout;
    for (int i = 0; i <= limit; i++)
    {
        fout.open("output.out", ios::app);
        fout << "Iteration " << i << ": " << src << " ";
        fout.close();
        if (DLS(src, goal, i) == 1)
        {
            return 1;
        }
        fout.open("output.out", ios::app);
        fout << "\n";
        fout.close();
    }
    return -1;
}

void IDS::runIDS(string filein, string filein2, int src, int goal, int limit)
{
    clock_t start = clock();
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "IDS\n";
    fout.close();
    InitIDS(filein, filein2);
    fout.open("output.out", ios::app);
    if(IDDFS(src,goal,limit)==1)
        fout<<"\nGoal node found within depth limit";
    else
        fout<<"\nGoal node not found !\n";
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fout << "\nDuration time IDS: " << time_taken * 1000 << " miliseconds";
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

double IDS::get_solution(bool is_ds){
    runIDS(Constants::FILEIN, Constants::FILEIN2, Constants::start, Constants::end, Constants::limit);
    return 0.0;
}
