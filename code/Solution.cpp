#include "Solution.h"

void Solution::solve(string path){
    int nodeNum , edgeNum , exitNum;

    cin >> nodeNum >> edgeNum >> exitNum ;
    graph = vector< vector<pair<int , int> > >(nodeNum , vector<pair<int , int> >() ) ;
    exit = vector<int>(exitNum , 0);
    nodePeople  = vector<int>(nodeNum , 0);

    for(int i = 0 ; i < nodeNum ; i++){
        int adjacentNodeNum ;
        cin >> adjacentNodeNum;
        graph[i] = vector<pair<int , int> >(adjacentNodeNum , pair<int,int>() );
        for(int j = 0 ; j < adjacentNodeNum ; j++){
            cin >> graph[i][j].first >> graph[i][j].second ;
        }
    }

    for(int i = 0 ; i < nodeNum ; i++){
        cin >> nodePeople[i] ;
    }


    for(int i = 0 ; i < exitNum ; i++){
        cin >> exit[i] ;
    }

    nowResult = generateFirstResult();
    saSolve();
}



int Solution::evaluate(vector< vector<pair<int , int> > > checkResult ){
    int value = 0;
    return value;
}

vector< vector<pair<int , int> > > Solution::generateFirstResult(){
    //todo
    vector< vector<pair<int , int> > > firstResult;
    return firstResult;
}


vector< vector<pair<int , int> > > Solution::generateNewResult(){
    //todo
    //use nowResult to generate new result
    vector< vector<pair<int , int> > > newResult = nowResult;;
    return newResult;

}

bool Solution::canAccept(double temperature , int newValue , int oldValue){
    // todo

    return true;
}


void Solution::saSolve(){
    bestResult = nowResult;
    int inLoop = 1000,
        outLoop = 1000;
    int nowValue = evaluate(nowResult);
    int bestValue = nowValue;

    double  temperature = 100,
            alpha = 0.95;

    for(int i = 0 ; i < outLoop ; i++ ){
        for(int j = 0 ; j < inLoop ; j++){
            vector< vector<pair<int , int> > > checkResult = generateNewResult();
            int newValue = evaluate(checkResult);

            if(canAccept(temperature , newValue , nowValue) ){
                nowResult = checkResult;
                nowValue = newValue;
                if(nowValue < bestValue){
                    bestValue = nowValue;
                    bestResult = nowResult;
                }
            }
        }
        temperature = temperature * alpha;

    }
}
