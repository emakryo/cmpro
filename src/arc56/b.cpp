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
const int Mmax = 2e5;
int N, M, S;
int U[Mmax], V[Mmax];

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
	cin >> N >> M >> S;
	S--;
	for(int i=0; i<M; i++){
		cin >> U[i] >> V[i];
		U[i]--; V[i]--;
	}


	vector<pair<int, int>> edges(M);
	for(int i=0; i<M; i++){
		if(V[i]<U[i]) swap(U[i], V[i]);
		edges[i] = {U[i], V[i]};
	}
	sort(edges.begin(), edges.end());
	reverse(edges.begin(), edges.end());

	UnionFind uf(N);
	int e=0;

	vector<int> ans;
	for(int i=N-1; i>=0; i--){
		while(e<M&&edges[e].first>=i){
			uf.unite(edges[e].first, edges[e].second);
			e++;
		}
		if(uf.same(S, i)) ans.push_back(i);
	}

	for(int i=ans.size()-1; i>=0; i--) cout << ans[i]+1 << endl;



	return 0;
}
