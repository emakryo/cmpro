#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 1e5;
int N;
ll X[Nmax], Y[Nmax];

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
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i];
	}

	vector<pair<ll, int> > xs(N);
	vector<pair<ll, int> > ys(N);
	for(int i=0; i<N; i++){
		xs[i] = make_pair(X[i], i);
		ys[i] = make_pair(Y[i], i);
	}
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());

	vector<pair<ll, pair<int, int> > > edge;
	for(int i=0; i<N-1; i++){
		edge.push_back(make_pair(xs[i+1].first-xs[i].first, make_pair(xs[i+1].second, xs[i].second)));
		edge.push_back(make_pair(ys[i+1].first-ys[i].first, make_pair(ys[i+1].second, ys[i].second)));
	}

	sort(edge.begin(), edge.end());

	UnionFind uf(N);
	ll ans = 0;
	for(int i=0; i<edge.size(); i++){
		int a = edge[i].second.first;
		int b = edge[i].second.second;
		if(!uf.same(a, b)){
			ans+=edge[i].first;
			uf.unite(a, b);
		}
	}

	cout << ans << endl;

	return 0;
}
