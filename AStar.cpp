#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include "Astar.h"
#include "Constants.h"
#include "memory.h"
using namespace std;
Astar::Astar(Network * g) : Framework(g)
{
}

Astar::~Astar()
{
}
#define MAX 100
#define TRUE 1
#define FALSE 0
#define VOCUNG 10000000
struct Node
{
	int index;  // so thu tu
	int g;      // khoang cach tu dinh ban dau den dinh hien ta
	int f;      // f = h + g;
	int h;      // duong di ngan nhat
	int color;  // danh dau dinh di qua
	int nutcha;    // dinh cha
};

Node node0;

vector <Node> p(MAX,node0);
vector <Node> Open(MAX,node0);
vector <Node> Close(MAX,node0);
vector<int> matrantrongso={14,15,6,7,8,12,10,4,4,0};

void Astar::InitAstar(string filein, int n, int s, int t, vector<vector<int>> &Matrix)
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


int Count(int n,vector <Node> Open)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (Open[i].color == 1)
			count++;
	}
	return count;
}

int Find(int n,vector <Node> Open)
{

	for (int i = 0; i < n; i++)
		if (Open[i].color == 1)
			return i;
    return -1;
}

int FindMin(int n,vector <Node> Open)
{
	int minIndex = Find(n, Open);
	int min = Open[minIndex].f;
	for (int i = 0; i < n; i++)
	{
		if (Open[i].f < min && Open[i].color == 1)
		{
			minIndex = i;
			min = Open[i].f;
		}
	}
	return minIndex;
}

void Init(int n, vector<int> b)
{
	for (int i = 0; i < n; i++)
	{
		p[i].index = i;
		p[i].color = 0;
		p[i].g = b[i];
		p[i].nutcha = 0;
		p[i].f = p[i].g;
		p[i].h = 0;
	}
}

int Findpoint(int n,vector <Node> q, int o)
{
	for (int i = 0; i < n; i++)
		if (q[i].index == o)
			return  i;
    return -1;
}

void Astar::alg_Astar( int n, int start, int finsh,vector<vector<int>> Matrix)
{
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
	int l = 0;
	Open[l] = p[start];
	Open[l].color = 1;
	Open[l].f = Open[l].h + Open[l].g;
	l++;
	int w = 0;

	while (Count(l, Open) != 0) // kiem tra xem tap Open co con phan tu nao khong
	{
		int k = FindMin(n, Open); // tim vi tri nho nhat trong Open
		Open[k].color = 2; // cho diem tim duoc vao Close
		Close[w] = Open[k];
		Close[w].color = 2;
		w++;
		p[Findpoint(n, p, Open[k].index)].color = 2;
		if (Findpoint(n, p, Open[k].index) == finsh)
		{   fout<<"A*";
			fout << "Duong di qua  la" << endl;
			fout << finsh << "\t";
			int y = Findpoint(w, Close, finsh);
			int u = Close[y].nutcha;
			fout<<u<<" ";
			while (u != start)
			{
				y = Findpoint(w, Close, u);
				u = Close[y].nutcha;
				fout << u << "\t";
			}

			fout<<endl<<"do dai duong di la"<<Close[w-1].h<<endl;
			break;
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (Matrix[Findpoint(n, p, Open[k].index)][i] != 0 && p[i].color == 0) // neu chua co trong Open va Close
				{
					Open[l] = p[i];
					Open[l].color = 1;
					Open[l].h = Matrix[Findpoint(n, p, Open[k].index)][i] + Open[k].h; // tinh h khoang cach ngan nhat tu dinh bat dau den dinh hien tai
					Open[l].f = Open[l].g + Open[l].h;
					Open[l].nutcha = Findpoint(n, p, Open[k].index);
					p[i].color = 1;
					l++;
				}
				if (Matrix[Findpoint(n, p, Open[k].index)][i] != 0 && p[i].color == 1) // neu dinh da co trong Open
				{
					int h = Findpoint(l, Open, p[i].index);
					Node tempNode = p[i];
					tempNode.color = 1;
					tempNode.h = Matrix[Findpoint(n, p, Open[k].index)][i] + Open[k].h;
					tempNode.nutcha = k;
					tempNode.f = tempNode.h + tempNode.g;
					if (tempNode.f < Open[h].f) // neu f trang thai hien tai be hon trang thai cap nhat truoc do
						Open[h] = tempNode;
				}

			}
		}
	}
}

void Astar::runAstar(string filein, int n, int s, int t, vector<vector<int>> &Matrix)
{
    clock_t start = clock();
    InitAstar(filein, n, s, t, Matrix);
    Init(n,matrantrongso);
    alg_Astar(n, s, t, Matrix);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_pER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time a*: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double Astar::get_solution(bool is_ds){
    //cout<<5;
    vector<vector<int>> Matrix;
    runAstar(Constants::FILEIN, Constants::n_nodes, Constants::start, Constants::end, Matrix);
    return 0.0;
}
