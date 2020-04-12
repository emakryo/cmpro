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
	int N, M;
	cin >> N >> M;
	vector<pair<int, pair<int, int>>> xs;
	for(int i=0; i<M; i++){
		int a, b, y;
		cin >> a >> b >> y;
		xs.push_back({2*y, {a-1, b-1}});
	}
	int Q;
	cin >> Q;
	vector<pair<int, int>> people;
	for(int i=0; i<Q; i++){
		int v, w;
		cin >> v >> w;
		xs.push_back({2*w+1, {i, v-1}});
	}

	sort(xs.begin(), xs.end());
	reverse(xs.begin(), xs.end());
	vector<int> ans(Q);
	UnionFind uf(N);
	for(int i=0; i<M+Q; i++){
		if(xs[i].first % 2 == 0) {
			uf.unite(xs[i].second.first, xs[i].second.second);
			debug("unite", xs[i].second.first, xs[i].second.second);
		} else {
			ans[xs[i].second.first] = uf.count(xs[i].second.second);
			debug("count", xs[i].second.first, xs[i].second.second);
		}
	}

	for(int i=0; i<Q; i++){
		cout << ans[i] << endl;
	}

	return 0;
}
