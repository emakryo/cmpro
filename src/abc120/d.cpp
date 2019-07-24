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
const int Mmax = 1e5;
int N, M, A[Mmax], B[Mmax];

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
	for(int i=0; i<M; i++){
		cin >> A[i] >> B[i];
		A[i]--; B[i]--;
	}

	ll total = (ll)N*(N-1)/2;
	vector<ll> ans(1, total);
	UnionFind uf(N);
	for(int i=M-1; i>=0; i--){
		if(uf.same(A[i], B[i])){
			ans.push_back(total);
		} else {
			total -= (ll)uf.count(A[i])*uf.count(B[i]);
			ans.push_back(total);
			uf.unite(A[i], B[i]);
		}
	}
	for(int i=M-1; i>=0; i--){
		cout << ans[i] << endl;
	}

	return 0;
}
