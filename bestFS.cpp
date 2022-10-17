#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
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

#define MAX 100
#define TRUE 1
#define FALSE 0
#define VOCUNG 10000000

vector<int> truoc2(MAX, 0);   // mảng đánh dấu đường đi.
vector<int> d2(MAX, 0);       // mảng đánh dấu khoảng cách.
vector<int> chuaxet2(MAX,0); // mảng đánh dấu đỉnh đã được gán nhãn.
vector<int> chuanbixet;
int dodai=0;
vector<int> trongso3={14,15,6,7,8,12,10,4,4,0};
void BestFS::InitBestFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix)
{
    fstream fin;
    fin.open(filein, ios::in);
    Matrix = vector<vector<int>>(MAX, vector<int>(MAX, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Matrix[i][j] = 0;
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        Matrix[u][v] = w;
        //Matrix[v][u] = w;
    }
    fin.close();
    //for (int i = 0; i < n; i++)
    //    for (int j = 0; j < n; j++)
    //        cout<<Matrix[i][j]<<" ";
}
int BestFS::sumOfMark(int s,int t,vector<vector<int>> Matrix)
{
    int res = 0;
    int i = t;
    while (i != s)
    {
        res+=Matrix[truoc2[i]][i];
        i=truoc2[i];
    }

    return res;
}
void BestFS::ResultBestFS(int s, int t,vector<vector<int>> Matrix)
{
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "BestFS\n";
    fout << "Duong di ngan nhat tu " << s << " den " << t << " la" << endl;
    fout << t << "<=";
    int i = truoc2[t];
    while (i != s)
    {
        fout << i << "<=";
        i = truoc2[i];
    }
    fout << s;
    fout << endl
         << "Do dai duong di la : "<<sumOfMark(s,t,Matrix);
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

void BestFS::alg_BestFS(int n, int s, int t, vector<vector<int>> Matrix)
{
    chuaxet2[s]=1;
    for(int i=0;i<n;i++){
        if(Matrix[s][i]>0){
            chuanbixet.push_back(i);
            truoc2[i]=s;
        }
    }
    int minpp=1000;
    int xettiep;//luu diem nho nhat de xet tiep theo
    for(int i=0;i<chuanbixet.size();i++){
        if(trongso3[chuanbixet[i]]<minpp&&chuaxet2[chuanbixet[i]]==0){
            minpp=trongso3[chuanbixet[i]];
            xettiep=i;
        }
    }

    int xettiep2=chuanbixet[xettiep];
    if(xettiep2==t){
        //cout<<"ahihi";
        //d2[t]=sumOfMark(s,t,Matrix);
    }
    else{
       chuanbixet.erase(chuanbixet.begin()+xettiep);
        alg_BestFS(n,xettiep2,t,Matrix);
    }

}

void BestFS::runBestFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix)
{
    // BFS
    //cout<<2;
    clock_t start = clock();
    InitBestFS(filein, n, s, t, Matrix);
    alg_BestFS(n, s, t, Matrix);
    ResultBestFS(s, t,Matrix);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time BFS: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double BestFS::get_solution(bool is_ds){
    //cout<<5;
    vector<vector<int>> Matrix;
    runBestFS(Constants::FILEIN, Constants::n_nodes, Constants::start, Constants::end, Matrix);
    return 0.0;
}
