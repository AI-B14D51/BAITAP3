#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
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

#define MAX 100
int dMin2 = 1e8;                   
vector<bool> visited2(MAX, false); 
vector<int> mark2, res2;   

void Init_HC(string filein,string filein2, vector<vector<int>> &Matrix, vector<int> &thamsodinh) {
    Matrix = vector<vector<int>>(MAX, vector<int>(MAX, 0));
    thamsodinh = vector<int>(MAX,0);
    int u, v, w, a, b;
    fstream fin,fin2;
    fin.open(filein, ios::in);
    while (!fin.eof())
    {
    	fin >>u >>v >>w;
    	Matrix[u][v] = w;
        Matrix[v][u] = w;
    }
    fin.close();  
    fin2.open(filein2, ios::in);
    while (!fin2.eof())
    {
        fin2 >> a >> b;
        thamsodinh[a]=b;
	}
	fin2.close();
}


int SumOfMark(vector<vector<int>> Matrix)
{
    int res = 0;
    for (int i = 0; i < mark2.size() - 1; i++)
    {
        res += Matrix[mark2[i]][mark2[i+1]];
    }
    return res;
}

void Xuly_HC(int n, int u, int t, vector<vector<int>> Matrix, vector<int> thamsodinh)
{
    int thamsodinh_min=100;
    for (int i = 0; i < n; i++)
    {
        if(!visited2[i] && Matrix[u][i]&&thamsodinh[i]< thamsodinh_min){
            thamsodinh_min=thamsodinh[i];
            }
        }
    for (int i = 0; i < n; i++)
    {
        if(!visited2[i] && Matrix[u][i]&&thamsodinh[i]== thamsodinh_min){
            mark2.push_back(i);
            visited2[i] = true;
            if (i == t)
            {
                if (SumOfMark(Matrix) < dMin2)
                {
                    dMin2 = SumOfMark(Matrix);
                    res2 = mark2;
                }
                break;
                mark2.pop_back();
                visited2[i] = false;

            }
            else
            {
                Xuly_HC(n, i, t, Matrix, thamsodinh);
                mark2.pop_back();
                visited2[i] = false;
            }
            }

        }
    }


void Result_HC(int s, int t){
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "HillClimb\n";
    fout << "Duong di ngan nhat tu " << s << " den " << t << " la:" << endl;
    for (int i = 0; i < res2.size() - 1; i++)
    {
        fout << res2[i] << "=>";
    }
    fout << res2[res2.size() - 1];
    fout << endl;
    fout << "Do dai duong di la : ";
    fout << dMin2;
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

void Run_HC(string filein, string filein2, int n, int s, int t, vector<vector<int>> &Matrix, vector<int> &thamsodinh) {
    clock_t start = clock();
    Init_HC(filein, filein2, Matrix, thamsodinh);
    mark2.push_back(s);
    visited2[s] = true;
    Xuly_HC(n, s, t, Matrix, thamsodinh);
    Result_HC(s, t);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "thoi gian: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double HillClimb::get_solution(bool is_ds)
{
	vector<vector<int>> Matrix;
	vector<int> thamsodinh;
    	Run_HC(Constants::FILEIN, Constants::FILEIN2, Constants::n_nodes, Constants::start, Constants::end, Matrix, thamsodinh);
	return 0.0;
}
