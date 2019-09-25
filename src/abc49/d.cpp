#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

struct UnionFind{
	std::vector<int> par, rnk, cnt;
	UnionFind(int n){
		par.assign(n, 0);
		rnk.assign(n, 0);
		cnt.assign(n, 1);
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
	int N, K, L;
	cin >> N >> K >> L;
	UnionFind uf1(N), uf2(N);
	for(int i=0; i<K; i++){
		int p, q;
		cin >> p >> q;
		uf1.unite(p-1, q-1);
	}
	for(int i=0; i<L; i++){
		int r, s;
		cin >> r >> s;
		uf2.unite(r-1, s-1);
	}

	vector<pair<pair<int, int>, int>> ps;
	for(int i=0; i<N; i++){
		ps.push_back({{uf1.root(i), uf2.root(i)}, i});
	}
	sort(ps.begin(), ps.end());
	UnionFind uf3(N);
	for(int i=0; i<N-1; i++){
		if(ps[i].first==ps[i+1].first) uf3.unite(ps[i].second, ps[i+1].second);
	}

	for(int i=0; i<N; i++){
		cout << uf3.count(i) << (i==N-1?"\n":" ");
	}

	return 0;
}
