//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 500;
int N, M, W;
int dist[Nmax];

struct edge {
	int from, to, cost;
};


int main(){
	int F;
	scanf("%d", &F);

	for(int F_iterator=0; F_iterator<F; F_iterator++){
		scanf("%d%d%d", &N, &M, &W);
		vector<edge> edges;
		edge e;
		for(int i=0; i<M; i++){
			scanf("%d%d%d", &e.from, &e.to, &e.cost);
			e.from--;
			e.to--;
			edges.push_back(e);
			swap(e.from, e.to);
			edges.push_back(e);
		}

		for(int i=0; i<W; i++){
			scanf("%d%d%d", &e.from, &e.to, &e.cost);
			e.from--;
			e.to--;
			e.cost = -e.cost;
			edges.push_back(e);
		}

		vector<int> dist(N, 0);

		bool neg_loop = false;
		for(int i=0; i<N; i++){
			for(int j=0; j<edges.size(); j++){
				e = edges[j];
				if(dist[e.to] > dist[e.from] + e.cost){
					dist[e.to] = dist[e.from] + e.cost;
					if(i == N-1) neg_loop = true;
				}
			}
		}

		if(neg_loop){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}

	return 0;
}
