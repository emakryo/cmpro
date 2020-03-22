#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

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
	int N, M, K;
	cin >> N >> M >> K;

	vector<pair<int, int>> F(M);
	for(int i=0; i<M; i++){
		cin >> F[i].first >> F[i].second;
		F[i].first--;
		F[i].second--;
		if(F[i].first > F[i].second) swap(F[i].first, F[i].second);
	}
	vector<pair<int, int>> B(K);
	for(int i=0; i<K; i++){
		cin >> B[i].first >> B[i].second;
		B[i].first--;
		B[i].second--;
		if(B[i].first > B[i].second) swap(B[i].first, B[i].second);
	}

	UnionFind uf(N);
	for(int i=0; i<M; i++){
		uf.unite(F[i].first, F[i].second);
	}

	vector<int> ans(N);
	for(int i=0; i<N; i++){
		ans[i] = uf.count(i)-1;
	}

	for(int i=0; i<M; i++){
		ans[F[i].first]--;
		ans[F[i].second]--;
	}

	for(int i=0; i<K; i++){
		if(uf.same(B[i].first, B[i].second)){
			ans[B[i].first]--;
			ans[B[i].second]--;
		}
	}

	for(int i=0; i<N; i++) cout << ans[i] << (i==N-1?'\n':' ');

	return 0;
}
