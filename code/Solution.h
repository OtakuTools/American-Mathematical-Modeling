#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <assert.h>

using namespace std;

class Solution{

public:
    void solve(string path);
private:


    vector<int> exit, tag, parent, temp_parent;
    vector<double> capacity,
                   maxCapacity,
                   speed;
    map<int, int> encode;
    vector< vector<pair<int , int> > >  graph,
                                        bestResult,
                                        nowResult;


    int evaluate(vector< vector<pair<int , int> > > checkResult );
    void read(int);
    void saSolve();
    bool canAccept(double temperature , int newValue , int oldValue);
    void generateFirstResult();
    vector< vector<pair<int , int> > > generateNewResult();

};


#endif // SOLUTION_H_INCLUDED
