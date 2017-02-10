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

class UnionFind{
	vector<int> par, rnk;
	public:
	UnionFind(int n){
		par=vector<int>(n);
		rnk=vector<int>(n,0);
		for(int i=0; i<n; i++) par[i]=i;
	}
	int root(int i){
		if(par[i]==i) return i;
		return par[i]=root(par[i]);
	}
	void unite(int i, int j){
		int ri = root(i);
		int rj = root(j);
		if(ri==rj) return;

		if(rnk[ri]==rnk[rj]){
			par[ri] = rj;
			rnk[rj]++;
		}
		else if(rnk[ri] < rnk[rj]){
			par[ri] = rj;
		}
		else{
			par[rj] = ri;
		}
	}
	bool same(int i, int j){
		return root(i) == root(j);
	}
};

int main(){
	int N, M;
	scanf("%d%d", &N, &M);
	vector<int> X(N), Y(N);
	for(int i=0; i<N; i++){
		int x,y;
		scanf("%d%d", &x, &y);
		X[i] = x;
		Y[i] = y;
	}
	vector<int> P(M), Q(M);
	vector<pair<double, int> > edges(M);
	double total=0;
	for(int i=0; i<M; i++){
		int p,q;
		scanf("%d%d",&p,&q);
		p--;
		q--;
		P[i] = p;
		Q[i] = q;
		double cost = sqrt((X[p]-X[q])*(X[p]-X[q])+(Y[p]-Y[q])*(Y[p]-Y[q]));
		edges[i] = make_pair(-cost, i);
		total += cost;
	}

	sort(edges.begin(), edges.end());

	UnionFind uf(N);
	for(int i=0; i<M; i++){
		int k = edges[i].second;
		if(!uf.same(P[k], Q[k])){
			uf.unite(P[k], Q[k]);
			total += edges[i].first;
		}
	}

	printf("%lf\n", total);

	return 0;
}
