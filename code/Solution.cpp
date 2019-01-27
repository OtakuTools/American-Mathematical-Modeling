#include "Solution.h"

void Solution::read(int nodes) {
    ifstream ifs;
    ifs.open("table.txt");
    for(int i = 0; i < nodes; i++) {
        int a,b;
        ifs >> a >> b;
        encode[a] = b;
    }
    ifs.close();
}

void Solution::solve(string path){
    int nodeNum , exitNum;
    ifstream ifs;
    ifs.open(path.c_str());
    ifs >> nodeNum >> exitNum ;
    graph = vector< vector<pair<int , int> > >(nodeNum , vector<pair<int , int> >() ) ;
    exit = vector<int>(exitNum , 0);
    capacity = vector<double>(nodeNum , 0);
    tag = vector<int>(nodeNum , -1);
    parent = vector<int>(nodeNum , 0);
    maxCapacity = vector<double>(nodeNum , 0);
    speed = vector<double>(exitNum , 10000);
    nowResult = vector< vector<pair<int,int> > >(nodeNum, vector<pair<int , int> >() );

    for(int i = 0 ; i < nodeNum ; i++){
        int adjacentNodeNum ;
        ifs >> adjacentNodeNum;
        graph[i] = vector<pair<int , int> >(adjacentNodeNum , pair<int,int>() );
        for(int j = 0 ; j < adjacentNodeNum ; j++){
            ifs >> graph[i][j].first >> graph[i][j].second ;
        }
    }

    for(int i = 0 ; i < nodeNum ; i++){
        ifs >> capacity[i] >> maxCapacity[i];
    }

    for(int i = 0 ; i < nodeNum ; i++){
        cout << capacity[i] << " ";
    }
    cout <<endl;


    for(int i = 0 ; i < exitNum ; i++){
        ifs >> exit[i] ;
    }
    ifs.close();

    read(nodeNum);
    cout << "a" <<endl;
    generateFirstResult();
    cout << "b" <<endl;
    saSolve();
}

int Solution::evaluate(vector< vector<pair<int , int> > > checkResult ){
    double total = 0;
    int value = 0;
    int timer = 0;
    vector<double> t_capacity = capacity;
    for(int i = 0; i < exit.size(); i++) {
        total = 0;
        timer = 0;
        queue<int> q;
        q.push(exit[i]);
        while(!q.empty()){
            int pos = q.front();
            q.pop();
            total += t_capacity[pos];
            for(int j = 0; j < checkResult[pos].size(); j++) {
                q.push(checkResult[pos][j].first);
            }
        }
        //cout << "total finish" <<endl;
        // maxCapacity表示节点最大容量
        while(total > 0.01) {
            queue<int> node;
            node.push(exit[i]);
            total -= min(speed[i], t_capacity[exit[i]]);
            timer++;
            t_capacity[exit[i]] -= min(speed[i], t_capacity[exit[i]]);

            while(!node.empty()) {
                int pos = node.front();
                node.pop();
                double weight_total = 0;
                for(int j = 0; checkResult[pos].size() > 0 && j < checkResult[pos].size(); j++) {
                    weight_total += checkResult[pos][j].second;
                }
                int remain = maxCapacity[pos] - t_capacity[pos];
                for(int j = 0; checkResult[pos].size() > 0 && j < checkResult[pos].size(); j++) {
                    double sum = min(min(t_capacity[checkResult[pos][j].first], (double)checkResult[pos][j].second), remain * (checkResult[pos][j].second / weight_total));
                    t_capacity[checkResult[pos][j].first] -= sum;
                    t_capacity[pos] += sum;
                    node.push(checkResult[pos][j].first);
                }
            }
            if(timer == 7000){
                for(int c = 0; c < t_capacity.size(); c++){
                    if(t_capacity[c] > 29){
                        cout << c << " ";
                    }
                }
                //cout << "total: " << total <<endl;
                value = max(value, timer);
                break;
            }
        }
        //cout << total << endl;
        //cout << "sum finish" <<endl;
        value = max(value, timer);
    }
    cout << value <<endl;
    return value;
}

inline void display(map<int, int>& encodemap, vector< vector<pair<int , int> > >& nowResult) {
    ofstream cout;
    cout.open("result2.txt");
    cout << nowResult.size() << endl;
    vector<int> rec(nowResult.size(), 0);
    for(int i = 0; i < nowResult.size(); i++) {

        // cout << "node: " << encodemap[i] << endl;
        //for(int j = 0; j < nowResult[i].size(); j++) {
            //cout << encodemap[i] << " -> " <<encodemap[nowResult[i][j].first] << endl;
        //}

        for(int j = 0; j < nowResult[i].size(); j++){
            rec[nowResult[i][j].first]++;
        }
    }
    for(int j = 0; j < rec.size(); j++){
        cout << encodemap[j] << " -> " << rec[j] << endl;
    }
    cout.close();
}

void Solution::generateFirstResult(){
    queue<int> que;
    //push root
    for( int i = 0; i < exit.size() ; ++i ){
        que.push(exit[i]);
        tag[ exit[i] ] = exit[i];
        parent[ exit[i] ] = -1;
    }
    //BFS
    while( !que.empty() ){
        int nowNode = que.front();
        que.pop();

        // find all unused edge
        int Enum = graph[ nowNode ].size();
        for( int i=0; i<Enum ; ++i ){
            int nextNode = graph[ nowNode ][i].first;
            int edgeWeight = graph[ nowNode ][i].second;
            if( tag[nextNode] != -1 )
                continue;
            // tree insert
            pair<int,int> newEdge( nextNode , edgeWeight );
            nowResult[ nowNode ].push_back( newEdge );
            parent[ nextNode ] = nowNode;
            // tag the new node
            tag[ nextNode ] = tag[ nowNode ];
            // enqueue the new node
            que.push( nextNode );
        }
    }
    display(encode, nowResult);
}

vector< vector<pair<int , int> > > Solution::generateNewResult(){
    //todo
    //use nowResult to generate new result
    vector< vector<pair<int , int> > > newResult = nowResult;
    int pos = rand() % newResult.size();
    while(parent[pos] == -1) {
        pos = rand() % newResult.size();
    }

    vector<int> check(newResult.size(), 0);
    queue<int> que;
    que.push(pos);
    check[pos] = 1;
    while(!que.empty()) {
        int nowP = que.front();
        que.pop();
        for(int i = 0; i < newResult[nowP].size(); i++){
            if(check[newResult[nowP][i].first] == 0) {
                check[newResult[nowP][i].first] = 1;
                que.push(newResult[nowP][i].first);
            }
        }
    }
    vector<pair<int , int> > temp;
    for(int i = 0; i < graph[pos].size(); i++) {
        if(!(parent[pos] == graph[pos][i].first || check[graph[pos][i].first])) {
            temp.push_back(graph[pos][i]);
        }
    }
    if(temp.size() == 0){
        return nowResult;
    }
    int newPos = temp[int(rand() % temp.size())].first;
    //delete pos from its parent
    //cout << parent[pos] << " " << pos <<endl;
    for(vector<pair<int , int> >::iterator i = newResult[parent[pos]].begin(); i != newResult[parent[pos]].end();) {
        //cout << (*i).first << endl;
        if((*i).first == pos){
            cout << (*i).first << endl;
            i = newResult[parent[pos]].erase(i);
            break;
        }
        else {
            i++;
        }
    }
    // add pos to newPos
    parent[pos] = newPos;
    tag[pos] = tag[newPos];
    for(int i = 0; i < graph[newPos].size(); i++) {
        if(graph[newPos][i].first == pos){
            newResult[newPos].push_back(graph[newPos][i]);
            break;
        }
    }
    return newResult;
}

bool Solution::canAccept(double temperature , int newValue , int oldValue){
    // todo
    int delta_E = newValue - oldValue;
    if(delta_E <= 0) {
        return true;
    }
    else{
        double P = exp(-delta_E / temperature);
        double R = double(rand() % 999) / 1000;
        return R < P;
    }
}


void Solution::saSolve(){
    double beginT = 100, endT = 0.1, alpha = 0.9;
    double temperature = beginT;
    int inLoop = 200;
    int nowValue = evaluate(nowResult);
    int bestValue = nowValue;
    bestResult = nowResult;

    while(temperature >= endT){
        for(int j = 0 ; j < inLoop ; j++){
            //cout << "generate begin" << endl;
            vector< vector<pair<int , int> > > checkResult = generateNewResult();
            //cout << "generate end" << endl;
            //cout << "evaluate begin" << endl;
            int newValue = evaluate(checkResult);
            //cout << "evaluate end" << endl;
            if(newValue < 7000 && canAccept(temperature , newValue , nowValue)){
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
    display(encode, bestResult);
}
