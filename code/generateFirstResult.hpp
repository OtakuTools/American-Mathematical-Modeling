void Solution::generateFirstResult(){
	queue<int> que;

	//push root
	for( int i=0 ; i<K ; ++i ){
		que.push( exit[i] );
		tag[ exit[i] ] = i+1; 
	}
	//BFS
	while( !que.empty() ){
		int nowNode = que.top();
		que.pop();

		// find all unused edge
		int Enum = graph[ nowNode ].size();
		for( int i=0; i<Enum ; ++i ){
			int nextNode = graph[ nowNode ][i].first;
			int edgeWeight = graph[ nowNode ][i].second;
			if( tag[nextNode] == 0 )
				continue;
			// tree insert
			pair<int,int> newEdge( nextNode , edgeWeight );
			nowResult[ nowNode ].push_back( newEdge );
			// tag the new node
			tag[ nextNode ] = tag[ nowNode ];
			// enqueue the new node
			que.push( nextNode );
		}
	}
}