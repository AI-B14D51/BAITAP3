#include <iostream>
#include <omp.h>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <string>

#include "Network.h"
#include "Constants.h"
#include "DFS.h"
#include "BFS.h"
#include "bestFS.h"
#include "HillClimb.h"
#include "AStar.h"
//#include <time.h>
#include <chrono>
#include <iomanip> // setprecision
#if defined(_WIN32)
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif
using namespace std;

#pragma warning(disable : 4996)
vector<uint> B_vals = {15, 20, 25, 30, 35, 40, 45, 50};

vector<uint> M_vals = {3};
vector<double> Delta_vals = {1};

Network *g;

void print_help()
{
	cout << "Options: " << endl;
	cout << "-f <data filename>" << endl
		 << "-V <size of V> # default: 50" << endl
		 << "-t <type of experiment, 0: influence maximization, 1: sensor placement> # default: 0" << endl
		 << "-k <value of k> # default: 3" << endl
		 << "-B <value of B> # default: 10" << endl
		 << "-M <value of M> # default: 3" << endl
		 << "-e <value of epsilon> # default: 0.5 for IM and 0 for sensor placement" << endl
		 << "-n <value of eta - denoise step for RStream> # default: 2" << endl
		 << "-g <value of gamma> # default: 1.0" << endl
		 << "-a <algorithm, 0: greedy, 1: DStream, 2: RStream, 3: SGr>  # default: 1, please use SSA source code for testing IM algorithm" << endl
		 << "-p <number of threads to running algorithms> # default: 4" << endl;
}

pair<string, int> parseArgs(int argc, char **argv)
{
	string filename = "error";
	int no_nodes = 50;

	/*if (argc == 1) {
		print_help();
		return pair<string,int>(filename, no_nodes);
	}*/

	int i = 1;
	while (i < argc - 1)
	{
		string arg = argv[i];
		if (arg == "-f")
		{
			filename = argv[i + 1];
			Constants::FILEIN = argv[i + 1];
		}
		else if (arg == "-g" || arg == "-e")
		{
			string s_val = argv[i + 1];
			std::string::size_type sz;
			if (arg == "-g")
				Constants::DELTA = std::stod(s_val, &sz);
			else
				Constants::EPS = std::stod(s_val, &sz);
		}
		else
		{
			string s_val = argv[i + 1];
			std::string::size_type sz;
			int val = std::stoi(s_val, &sz);
			if (arg == "-t")
			{
				Constants::DATA = val == 0 ? Social : Sensor;
				if (Constants::DATA == Sensor)
				{
					Constants::EPS = 0;
					Constants::NO_DENOISE_STEPS = 1;
				}
			}
			else if (arg == "-V")
			{
				no_nodes = val;
				Constants::n_nodes = val;
			}
			else if (arg == "-k")
			{
				Constants::K = val;
			}
			else if (arg == "-B")
			{
				Constants::BUDGET = val;
			}
			else if (arg == "-n")
			{
				Constants::NO_DENOISE_STEPS = val;
				if (Constants::DATA == Sensor)
				{
					Constants::NO_DENOISE_STEPS = 1;
				}
			}
			else if (arg == "-M")
			{
				Constants::M = val;
			}
			else if (arg == "-a")
			{
				switch (val)
				{
				case 0:
					Constants::ALGORITHM = aDFS;
					break;
				case 1:
					Constants::ALGORITHM = aBFS;
					break;
				case 2:
					Constants::ALGORITHM = abestFS;
					break;
				case 3:
					Constants::ALGORITHM = aHill;
					break;
				case 4:
					Constants::ALGORITHM = aAstar;
					break;
				default:
					Constants::ALGORITHM = aDFS;
					break;
				}
			}
			else if (arg == "-p")
			{
				Constants::NUM_THREAD = val;
			}
			else if (arg == "-st")
			{
				Constants::start = val;
			}
			else if (arg == "-en")
			{
				Constants::end = val;
			}
			else if (arg == "-l")
			{
				Constants::limit = val;
			}
		}
		i += 2;
	}
	// cout << Constants::start << " " << Constants::end << " " << Constants::ALGORITHM;
	return pair<string, int>(filename, no_nodes);
}

void run_command(string filename, int no_nodes)
{
	Network *g = new Network();
	

	if (false)
	{
		cout << "Wrong file, format or arguments" << endl;
		print_help();
	}
	else
	{
		double sol = 0.0;
		int no_queries = 0;
		omp_set_num_threads(Constants::NUM_THREAD);
		switch (Constants::ALGORITHM)
		{
		case aDFS:
		{
			DFS *dfs = new DFS(g);
			dfs->get_solution();
			delete dfs;
			break;
		}
		case aBFS:
		{
			BFS *bfs = new BFS(g);
			bfs->get_solution();
			delete bfs;
			break;
		}
		case abestFS:
		{
			bestFS *bestfs = new bestFS(g);
			bestfs->get_solution();
			delete bestfs;
			break;
		}
		case aHill:
		{
			HillClimb *Hill = new HillClimb(g);
			Hill->get_solution();
			delete Hill;
			break;
		}
		case aAstar:
		{
			AStar *astar = new AStar(g);
			astar->get_solution();
			delete astar;
			break;
		}
		default:
		{
			DFS *dfs = new DFS(g);
			dfs->get_solution();
			delete dfs;
			break;
		}
		}
		// if (Constants::DATA == Sensor) sol = sol / 100;
		// cout << "Output: " << sol << endl
		// 	<< "Number of queries: " << no_queries << endl;
	}
	delete g;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	pair<string, int> r = parseArgs(argc, argv);
	if (r.first == "error")
	{
		cout << "Wrong file, format or arguments" << endl;
		print_help();
	}
	else
		run_command(r.first, r.second);

	return 0;
}
