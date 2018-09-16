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
int N, M, A[Nmax], B[Nmax];
int Q, X[Nmax], Y[Nmax], Z[Nmax];

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

	cin >> Q;
	for(int i=0; i<Q; i++){
		cin >> X[i] >> Y[i] >> Z[i];
		X[i]--; Y[i]--;
	}

	vector<int> lb(Q, 0), ub(Q, M);
	vector<pair<int, int> > med(Q);
	while(true){
		for(int i=0; i<Q; i++){
			med[i] = make_pair((ub[i]+lb[i])/2, i);
		}
		sort(med.begin(), med.end());

		int k=0;
		while(med[k].first==0) k++;
		UnionFind uf(N);
		for(int i=0; i<M; i++){
			uf.unite(A[i], B[i]);
			while(med[k].first-1==i){
				int m = med[k].first;
				int j = med[k].second;
				k++;
				if(ub[j]-lb[j]<=1) continue;
				int n = uf.same(X[j], Y[j]) ? uf.count(X[j]) : uf.count(X[j])+uf.count(Y[j]);
				if(n >= Z[j]){
					ub[j] = m;
				} else {
					lb[j] = m;
				}
			}
		}

		bool done = true;
		for(int i=0; i<Q; i++){
			if(ub[i]-lb[i]>1){
				done=false;
			}
		}
		if(done) break;
	}

	for(int i=0; i<Q; i++){
		cout << ub[i] << endl;
	}

	return 0;
}
