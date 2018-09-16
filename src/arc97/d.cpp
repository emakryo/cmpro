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
int N, M, P[Nmax], X[Nmax], Y[Nmax];

class UnionFind{
	vector<int> par, rnk, cnt;
	public:
	UnionFind(int n){
		par=vector<int>(n);
		rnk=vector<int>(n,0);
		cnt=vector<int>(n,1);
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
			cnt[rj] += cnt[ri];
			par[ri] = rj;
			rnk[rj]++;
		}
		else if(rnk[ri] < rnk[rj]){
			cnt[rj] += cnt[ri];
			par[ri] = rj;
		}
		else{
			cnt[ri] += cnt[rj];
			par[rj] = ri;
		}
	}
	bool same(int i, int j){
		return root(i) == root(j);
	}
	int count(int i){
		return cnt[root(i)];
	}
};

int main(){
	cin >> N >> M;
	for(int i=0; i<N; i++){
		cin >> P[i];
		P[i]--;
	}
	for(int i=0; i<M; i++){
		cin >> X[i] >> Y[i];
		X[i]--; Y[i]--;
	}

	UnionFind uf(N);
	for(int i=0; i<M; i++){
		uf.unite(X[i], Y[i]);
	}

	int ans = 0;
	for(int i=0; i<N; i++){
		if(uf.same(P[i], i)) ans++;
	}

	cout << ans << endl;

	return 0;
}
