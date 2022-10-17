#include "Constants.h"
using namespace std;


Constants::Constants()
{
}

Constants::~Constants()
{
}

ALG Constants::ALGORITHM = aDFS;
DATATYPE Constants::DATA = Social;
int Constants::NUM_THREAD = 70;
double Constants::DELTA = 1.0;
int Constants::K = 1;
int Constants::BUDGET = 10;
int Constants::M = 3;
int Constants::start = 0;
int Constants::end = 3;
string Constants::FILEIN = "input.in";
int Constants::n_nodes = 20;
int Constants::limit = 10;
std::vector<int> Constants::cost_matrix ={20,10,5,0,30,12,16,25,24,22,16,11,19,10,8,15,17,18,19,20};

// for social
double Constants::EPS = 0.5;
int Constants::NO_DENOISE_STEPS = 2;

// for sensor
//double Constants::EPS = 0.0;
//int Constants::NO_DENOISE_STEPS = 1;
