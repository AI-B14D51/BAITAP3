#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <map>
#include "Hillclimbing.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

#define MAX 100

Hillclimbing::Hillclimbing(Network * g) : Framework(g)
{
}

Hillclimbing::~Hillclimbing()
{
}

vector<bool> visitedHC(MAX, false);
vector<int> markHC, resHC;

void InitHC(string filein, vector<vector<int>> &Matrix) {
    fstream fin;
    fin.open(filein, ios::in);
    Matrix = vector<vector<int>>(MAX, vector<int>(MAX, 0));
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        Matrix[u][v] = w;
        Matrix[v][u] = w;
    }
    fin.close();
}

int findMin(int n, int u, vector<vector<int>> Matrix) {
    int res = -1, Min = 1e8;
    for(int i = 0; i < n; i++) {
        if(Matrix[u][i] && !visitedHC[i] && Matrix[u][i] < Min) {
            res = i;
            Min = Matrix[u][i];
        }
    }
    return res;
}

void alg_HC(int n, int st, int en, vector<vector<int>> Matrix) {
    visitedHC[st] = true;
    markHC.push_back(st);
    if(st == en) {
        resHC = markHC;
        visitedHC[st] = false;
        markHC.pop_back();
        return;
    } 
    int u = findMin(n, st, Matrix);
    if (u == -1)
        return;
    
    if(u == en) {
        markHC.push_back(u);
        resHC = markHC;
        return;
    } else {
        alg_HC(n, u, en, Matrix);
        visitedHC[st] = false;
        markHC.pop_back();
    }
}

void resultHC() {
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "Hill Climbing\n";
    fout << "Duong di: ";
    for(int i = 0; i < resHC.size()-1; i++) {
        fout << resHC[i] << "->";
    }
    fout << resHC[resHC.size() -1] << "\n";
    fout.close();
}

void run_Hillclimbing(string filein,int n, int Src, int target){
    clock_t start = clock();
    vector<vector<int>> Matrix;
    InitHC(filein, Matrix);
    alg_HC(n, Src,target, Matrix);
    resultHC();
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time Hill Climbing: " << time_taken * 1000 << " miliseconds";
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

double Hillclimbing::get_solution(bool is_ds){
    run_Hillclimbing(Constants::FILEIN,Constants::n_nodes,Constants::start,Constants::end);
    return 0.0;
}