#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED
#include <vector>
#include <iostream>

using namespace std;

class Solution{

public:
    void solve(string path);
private:


    vector<int> exit,
                nodePeople ;
    vector< vector<pair<int , int> > >  graph,
                                        bestResult,
                                        nowResult;


    int evaluate(vector< vector<pair<int , int> > > checkResult );
    void saSolve();
    bool canAccept(double temperature , int newValue , int oldValue);
    vector< vector<pair<int , int> > > generateFirstResult();
    vector< vector<pair<int , int> > > generateNewResult();

};


#endif // SOLUTION_H_INCLUDED
