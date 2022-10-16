#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <map>
#include "HillClimb.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

#define MAX 100

HillClimb::HillClimb(Network * g) : Framework(g)
{
}

HillClimb::~HillClimb()
{
}

vector<bool> visitedHC(MAX, false);
vector<int> markHC, resHC;

void InitHC(string filein,string filein2, vector<vector<int>> &Matrix) {
    Matrix = vector<vector<int>>(MAX, vector<int>(MAX, 0));
    
    int u, v, w, a, b;
    fstream fin,fin2;
    fin2.open(filein2, ios::in);
    {
    	fin2 >>a >>b;
    	fin.open(filein, ios::in);
      while (!fin.eof())
    {
        fin >> u >> v >> w;
        if(a==u){
        	w=w+b;
        	Matrix[u][v] = w;
        	Matrix[v][u] = w;
		}
	}
		fin.close();  
	}
	fin2.close();
}


void Xuly_HC(int n, int s, int t, vector<vector<int>> Matrix) {
    
}

void ResultHC() {
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

double HillClimb::get_solution(bool is_ds){
    clock_t start = clock();
    vector<vector<int>> Matrix;
    InitHC(Constants::FILEIN, Constants::FILEIN2, Matrix);
    Xuly_HC(Constants::n_nodes, Constants::start, Constants::end, Matrix);
    ResultHC();
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time Hill Climbing: " << time_taken * 1000 << " miliseconds";
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    return 0.0;
}
