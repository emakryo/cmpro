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
int N, Q;
const int Qmax=1e5;
int W[Qmax], X[Qmax], Y[Qmax], Z[Qmax];

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
	cin >> N >> Q;
	UnionFind uf(N);
	vector<int> odd(N, -1);
	for(int i=0; i<Q; i++){
		int w, x, y, z;
		cin >> w >> x >> y >> z;
		x--; y--;
		if(w==1){
			if(z%2){
				if(odd[x]<0) odd[x] = y;
				else uf.unite(odd[x], y);

				if(odd[y]<0) odd[y] = x;
				else uf.unite(odd[y], x);
			} else {
				uf.unite(x, y);
				if(odd[x]<0 && odd[y]>=0) odd[x]=odd[y];
				else if(odd[x]>=0 && odd[y]<0) odd[y]=odd[x];
				else if(odd[x]>=0 && odd[y]>=0) uf.unite(odd[x], odd[y]);
			}
		} else {
			//for(int i=0; i<N; i++) cout << odd[i] << (i<N-1?' ':'\n');
			cout << i << " " << (uf.same(x, y)?"YES":"NO") << endl;
		}
	}

	return 0;
}
