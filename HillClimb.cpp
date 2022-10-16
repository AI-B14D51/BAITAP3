#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "HillClimb.h"
#include "Constants.h"
#include "memory.h"
using namespace std;


HillClimb::HillClimb(Network * g) : Framework(g)
{
}

HillClimb::~HillClimb()
{
}
#define max 100
typedef pair<int,int> ii;
bool visitedHC[max];
vector<ii> graphHC[max]; 
vector<int> markHC;
bool found = false;
vector<int> resultHC;
bool compare(ii a, ii b){
    return a.second < b.second;
}
void input_HC(string filename) {
    fstream fin;
    fin.open(filename, ios::in);
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        graphHC[u].push_back(make_pair(v,w));
        graphHC[v].push_back(make_pair(u,w));
    }
    for(int i = 0; i < 100; i++){
        sort(graphHC[i].begin(),graphHC[i].end(),compare);
    }
    fin.close();
}


void execute_HC(int vt, int destination) {
    if(found) return;
    for (int i = 0; i < graphHC[vt].size(); i++)
    {
        int v = graphHC[vt][i].first;
        if (!visitedHC[v])
        {
            visitedHC[v] = true;
            if (v == destination)
            {
                markHC.push_back(v);
                resultHC = markHC;
                found = true;
                return;
            }
            else
            {
                markHC.push_back(v);
                execute_HC(v,destination);
                visitedHC[v] = false;
                markHC.pop_back();
            }
        }
    }
}

void print_HC() {
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "Hill Climbing" << endl;
    fout << "Path: ";
    for(int i = 0; i < resultHC.size()-1; i++) {
        fout << resultHC[i] << "->";
    }
    fout << resultHC[resultHC.size() -1] << endl;
    fout.close();
}

double HillClimb::get_solution(bool is_ds){
    clock_t start = clock();
    input_HC(Constants::FILEIN);
    execute_HC(Constants::start, Constants::end);
    print_HC();
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Time taken by Hill Climbing: " << time_taken * 1000 << " miliseconds";
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    return 0.0;
}